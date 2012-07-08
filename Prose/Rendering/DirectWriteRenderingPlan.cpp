#include "pch.h"
#include "DirectWriteRenderingPlan.h"

using namespace Platform::Collections;

using namespace Prose::Rendering;

using namespace Microsoft::WRL;

using namespace Windows::Foundation;
using namespace Windows::UI::Xaml;

bool Overlaps(Windows::Foundation::Rect left, RECT right) {
	return
		left.Left < right.right && left.Right > right.left &&
		left.Top < right.bottom && left.Bottom > right.top;
}

DirectWriteRenderingPlan::DirectWriteRenderingPlan(DirectWriteRenderer^ renderer) : _attached(false), _renderer(renderer), _surfaces(ref new Vector<DirectWriteSurface^>()) {
	TrackCreation(L"DirectWriteRenderingPlan");
}

DirectWriteRenderingPlan::~DirectWriteRenderingPlan(void) {
	if(_attached && _surface) {
		_surface->RegisterForUpdatesNeeded(nullptr);
	}

	TrackDestruction(L"DirectWriteRenderingPlan");
}

Size DirectWriteRenderingPlan::RenderSize::get() {
	if(!_renderSizeCalculated) {
		float width = 0.0;
		float height = 0.0;
		for each(auto surface in Surfaces) {
			width = max(width, surface->LayoutBounds.Width);
			height += surface->LayoutBounds.Height;
		}
		_renderSize = SizeHelper::FromDimensions(width, height);
	}
	return _renderSize;
}

void DirectWriteRenderingPlan::RenderSurface(DirectWriteSurface^ surface, ComPtr<ID2D1RenderTarget> renderTarget, ComPtr<ID2D1SolidColorBrush> brush) {
	D2D1_POINT_2F origin = D2D1::Point2F(surface->RenderArea.Left, surface->RenderArea.Top);

#ifdef TRACE_RENDER
	D2D1_MATRIX_3X2_F matrix;
	renderTarget->GetTransform(&matrix);
	D2D1::Matrix3x2F* mat = D2D1::Matrix3x2F::ReinterpretBaseType(&matrix);
	D2D1_POINT_2F xformed = mat->TransformPoint(origin);

	Platform::String^ str = "<unknown>";
	if(surface->Box->Spans->Size > 0) {
		str = surface->Box->Spans->GetAt(0)->Text;
	}
	if(str->Length() > 15) {
		std::wstring wstr(str->Data());
		wstr = wstr.substr(0, 15) + std::wstring(L"...");
		str = ref new Platform::String(wstr.c_str());
	}

	dbgf(L"Rendering Surface [%s] to (x=%f,y=%f)", str->Data(), xformed.x, xformed.y);
#endif
	
	renderTarget->DrawTextLayout(
		origin,
		surface->Layout.Get(),
		brush.Get(),
		D2D1_DRAW_TEXT_OPTIONS_NONE);

#ifdef SHOW_SURFACE_BORDERS
	ComPtr<ID2D1SolidColorBrush> yellowBrush;
	ThrowIfFailed(renderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Yellow, 0.75F), &yellowBrush));
	
	D2D1_RECT_F rect = D2D1::RectF(origin.x, origin.y, origin.x + surface->Metrics.width, origin.y + surface->Metrics.height);
	renderTarget->DrawRectangle(
		&rect,
		yellowBrush.Get(),
		5.0F);
#endif
}

void DirectWriteRenderingPlan::UpdatesNeeded() {
	ULONG drawingBoundsCount = 0;
	ThrowIfFailed(_surface->GetUpdateRectCount(&drawingBoundsCount));
	std::unique_ptr<RECT[]> drawingBounds(new RECT[drawingBoundsCount]);
	ThrowIfFailed(_surface->GetUpdateRects(drawingBounds.get(), drawingBoundsCount));
	
	for(ULONG i = 0; i < drawingBoundsCount; i++) {
#ifdef TRACE_RENDER
		dbgf(L"Redrawing (l=%d, t=%d, r=%d, b=%d)", drawingBounds[i].left, drawingBounds[i].top, drawingBounds[i].right, drawingBounds[i].bottom);
#endif

		// Start the drawing session
		ComPtr<IDXGISurface> dxgiSurface;
		POINT origin;
		ThrowIfFailed(_surface->BeginDraw(drawingBounds[i], &dxgiSurface, &origin));

		// Create the render target
		ComPtr<ID2D1RenderTarget> renderTarget;
		D2D1_RENDER_TARGET_PROPERTIES properties = D2D1::RenderTargetProperties(
			D2D1_RENDER_TARGET_TYPE_DEFAULT,
			D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED));
		ThrowIfFailed(DX::GetD2DFactory()->CreateDxgiSurfaceRenderTarget(
			dxgiSurface.Get(),
			&properties,
			&renderTarget));
	
		// TODO: This SOOOOOO needs to be specified by the consumer of this interface (i.e. the control!)
		ComPtr<ID2D1SolidColorBrush> whiteBrush;
		ThrowIfFailed(renderTarget->CreateSolidColorBrush(
			D2D1::ColorF(D2D1::ColorF::White),
			&whiteBrush));

		renderTarget->BeginDraw();
		renderTarget->Clear();

		// Set up the translation
		auto transform = D2D1::Matrix3x2F::Translation(
			(FLOAT)origin.x - (FLOAT)drawingBounds[i].left,
			(FLOAT)origin.y - (FLOAT)drawingBounds[i].top);
		renderTarget->SetTransform(transform);

		// Identify the nodes of the plan that are contained here and render them
		for each(auto renderSurface in Surfaces) {
			if(Overlaps(renderSurface->RenderArea, drawingBounds[i])) {
				RenderSurface(renderSurface, renderTarget, whiteBrush);
			}
		}

		renderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
		
		ThrowIfFailed(renderTarget->EndDraw());

		// End the drawing session
		ThrowIfFailed(_surface->EndDraw());
	}
}

void DirectWriteRenderingPlan::Attach(Windows::UI::Xaml::Media::Imaging::VirtualSurfaceImageSource^ targetSurface, Windows::Foundation::Rect region) {
	IInspectable* insp = reinterpret_cast<IInspectable*>(targetSurface);
	ThrowIfFailed(insp->QueryInterface(__uuidof(IVirtualSurfaceImageSourceNative), &_surface));

	// Set the device on the surface
	_renderer->Configure(_surface);

	ThrowIfFailed(_surface->Resize((int)(std::ceil(region.Width)), (int)(std::ceil(region.Height))));
	
	RECT nativeRect;
	DX::ToNativeRect(region, &nativeRect);
	ThrowIfFailed(_surface->Invalidate(nativeRect));
	
	_thunk = new VirtualSurfaceCallbackThunk();
	_thunk->Initialize(this);

	_surface->RegisterForUpdatesNeeded(_thunk.Get());
	_attached = true;
}