#include "pch.h"
#include "DirectWriteRenderer.h"
#include "RenderingLayoutVisitor.h"

using namespace Prose::Rendering;
using namespace Prose::Layout;
using namespace Microsoft::WRL;
using namespace Platform;

DirectWriteRenderer::DirectWriteRenderer(void) {
}

void DirectWriteRenderer::Render(IRenderingPlan^ plan, Windows::UI::Xaml::Media::Imaging::VirtualSurfaceImageSource^ targetSurface, Windows::Foundation::Rect region) {
	DirectWriteRenderingPlan^ dwPlan = safe_cast<DirectWriteRenderingPlan^>(plan);

	if(_knownTargetSurface == nullptr || !Object::ReferenceEquals(targetSurface, _knownTargetSurface)) {
		IInspectable* insp = reinterpret_cast<IInspectable*>(targetSurface);
		ThrowIfFailed(insp->QueryInterface(__uuidof(IVirtualSurfaceImageSourceNative), &_targetSurface));

		// Set up Direct2D Context
		InitializeDirect2D();

		// Set the device on the surface
		_targetSurface->SetDevice(_dxgiDevice.Get());
	}
	
	ThrowIfFailed(_targetSurface->Resize((int)(std::ceil(region.Width)), (int)(std::ceil(region.Height))));
	
	if(!_thunk) {
		_thunk = ComPtr<VirtualSurfaceCallbackThunk>(new VirtualSurfaceCallbackThunk());
		_thunk->Initialize(this, dwPlan);
	}

	_targetSurface->RegisterForUpdatesNeeded(_thunk.Get());
}

bool Overlaps(Windows::Foundation::Rect left, RECT right) {
	return
		left.Left < right.right && left.Right > right.left &&
		left.Top < right.bottom && left.Bottom > right.top;
}

void DirectWriteRenderer::UpdatesNeeded(DirectWriteRenderingPlan^ plan) {
	ULONG drawingBoundsCount = 0;
	ThrowIfFailed(_targetSurface->GetUpdateRectCount(&drawingBoundsCount));
	std::unique_ptr<RECT[]> drawingBounds(new RECT[drawingBoundsCount]);
	ThrowIfFailed(_targetSurface->GetUpdateRects(drawingBounds.get(), drawingBoundsCount));
	
	for(ULONG i = 0; i < drawingBoundsCount; i++) {
		// Start the drawing session
		ComPtr<IDXGISurface> surface;
		POINT origin;
		ThrowIfFailed(_targetSurface->BeginDraw(drawingBounds[i], &surface, &origin));

		// Create the render target
		ComPtr<ID2D1RenderTarget> renderTarget;
		D2D1_RENDER_TARGET_PROPERTIES properties = D2D1::RenderTargetProperties(
			D2D1_RENDER_TARGET_TYPE_DEFAULT,
			D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED));
		ThrowIfFailed(DX::GetD2DFactory()->CreateDxgiSurfaceRenderTarget(
			surface.Get(),
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
		for(UINT32 j = 0; j < plan->Surfaces->Size; j++) {
			auto surface = plan->Surfaces->GetAt(j);
			if(Overlaps(surface->Region, drawingBounds[i])) {
				RenderSurface(surface, renderTarget, whiteBrush);
			}
		}

		renderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
		
		ThrowIfFailed(renderTarget->EndDraw());

		// End the drawing session
		ThrowIfFailed(_targetSurface->EndDraw());
	}
}

void DirectWriteRenderer::RenderSurface(DirectWriteSurface^ surface, ComPtr<ID2D1RenderTarget> renderTarget, ComPtr<ID2D1SolidColorBrush> brush) {
	renderTarget->DrawTextLayout(
		D2D1::Point2F(surface->Region.Left, surface->Region.Top),
		surface->Layout.Get(),
		brush.Get(),
		D2D1_DRAW_TEXT_OPTIONS_NONE);
}

IRenderingPlan^ DirectWriteRenderer::PlanRendering(LayoutTree^ tree) {
	// Run the visitor
	RenderingLayoutVisitor^ visitor = ref new RenderingLayoutVisitor();
	tree->Accept(visitor);

	// Return the rendering plan
	return visitor->RenderingPlan;
}

void DirectWriteRenderer::InitializeDirect2D() {
	// Gotta intialize Direct3D first. Of course!
	UINT creationFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
	D3D_FEATURE_LEVEL featureLevels[] = 
    {
        D3D_FEATURE_LEVEL_11_1,
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1,
        D3D_FEATURE_LEVEL_10_0,
        D3D_FEATURE_LEVEL_9_3,
        D3D_FEATURE_LEVEL_9_2,
        D3D_FEATURE_LEVEL_9_1
    };
	D3D_FEATURE_LEVEL selectedFeatureLevel;
	
	ComPtr<ID3D11Device> d3d11device;
	ComPtr<ID3D11DeviceContext> deviceContext;
	ThrowIfFailed(D3D11CreateDevice(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		0,
		creationFlags,
		featureLevels,
		ARRAYSIZE(featureLevels),
		D3D11_SDK_VERSION,
		&d3d11device,
		&selectedFeatureLevel,
		&deviceContext));

	// Now we need a DXGI Device
	ComPtr<ID3D11Device1> device;
	ThrowIfFailed(d3d11device.As(&device));

	ThrowIfFailed(d3d11device.As(&_dxgiDevice));

	// We can create a Direct2D Device and Device Context now!
	ThrowIfFailed(DX::GetD2DFactory()->CreateDevice(_dxgiDevice.Get(), &_d2dDevice));
	ThrowIfFailed(_d2dDevice->CreateDeviceContext(D2D1_DEVICE_CONTEXT_OPTIONS_NONE, &_d2dDeviceContext));
}