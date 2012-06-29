#include "pch.h"
#include "DirectWriteRenderer.h"
#include "RenderingLayoutVisitor.h"

using namespace Prose::Rendering;
using namespace Prose::Layout;
using namespace Microsoft::WRL;
using namespace Platform;

DirectWriteRenderer::DirectWriteRenderer(void) {
}

void DirectWriteRenderer::Render(RenderingPlan^ plan, Windows::UI::Xaml::Media::Imaging::SurfaceImageSource^ targetSurface, Windows::Foundation::Rect region) {
	DirectWriteRenderingPlan^ dwPlan = safe_cast<DirectWriteRenderingPlan^>(plan);

	if(_knownTargetSurface == nullptr || !Object::ReferenceEquals(targetSurface, _knownTargetSurface)) {
		IInspectable* insp = reinterpret_cast<IInspectable*>(targetSurface);
		ThrowIfFailed(insp->QueryInterface(__uuidof(ISurfaceImageSourceNative), &_targetSurface));

		// Set up Direct2D Context
		InitializeDirect2D();

		// Set the device on the surface
		_targetSurface->SetDevice(_dxgiDevice.Get());
	}

	RECT target;
	DX::ToNativeRect(region, &target);

	// Start the drawing session
	ComPtr<IDXGISurface> surface;
	POINT offset;
	ThrowIfFailed(_targetSurface->BeginDraw(target, &surface, &offset));

	// Create the render target
	ComPtr<ID2D1RenderTarget> renderTarget;
	D2D1_RENDER_TARGET_PROPERTIES properties = D2D1::RenderTargetProperties(
		D2D1_RENDER_TARGET_TYPE_DEFAULT,
		D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED));
	ThrowIfFailed(DX::GetD2DFactory()->CreateDxgiSurfaceRenderTarget(
		surface.Get(),
		&properties,
		&renderTarget));

	// Render the invalidated surfaces
	RenderPlan(dwPlan, renderTarget);

	// Complete the drawing
	ThrowIfFailed(_targetSurface->EndDraw());
}

void DirectWriteRenderer::RenderPlan(DirectWriteRenderingPlan^ plan, ComPtr<ID2D1RenderTarget> target) {
	// TODO: This SOOOOOO needs to be specified by the consumer of this interface (i.e. the control!)
	ComPtr<ID2D1SolidColorBrush> whiteBrush;
	ThrowIfFailed(target->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF::White),
		&whiteBrush));

	target->BeginDraw();

	for(UINT32 i = 0; i < plan->Surfaces->Size; i++) {
		auto surface = plan->Surfaces->GetAt(i);

		D2D1_POINT_2F origin;
		origin.x = surface->Region.Left;
		origin.y = surface->Region.Top;

		target->DrawTextLayout(
			origin,
			surface->Layout.Get(),
			whiteBrush.Get(),
			D2D1_DRAW_TEXT_OPTIONS_NONE);
	}

	ThrowIfFailed(target->EndDraw());
}

RenderingPlan^ DirectWriteRenderer::PlanRendering(LayoutTree^ tree) {
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