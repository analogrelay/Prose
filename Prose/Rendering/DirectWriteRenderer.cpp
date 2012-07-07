#include "pch.h"
#include "DirectWriteRenderer.h"
#include "RenderingLayoutVisitor.h"

using namespace Prose::Rendering;
using namespace Prose::Layout;
using namespace Microsoft::WRL;
using namespace Platform;

DirectWriteRenderer::DirectWriteRenderer(void) {
}

IRenderingPlan^ DirectWriteRenderer::PlanRendering(LayoutTree^ tree) {
	// Run the visitor
	RenderingLayoutVisitor^ visitor = ref new RenderingLayoutVisitor(this);
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
	
	ComPtr<ID3D11DeviceContext> deviceContext;
	ThrowIfFailed(D3D11CreateDevice(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		0,
		creationFlags,
		featureLevels,
		ARRAYSIZE(featureLevels),
		D3D11_SDK_VERSION,
		&_d3d11Device,
		&selectedFeatureLevel,
		&_deviceContext));

	// Now we need a DXGI Device
	ThrowIfFailed(_d3d11Device.As(&_dxgiDevice));

	// We can create a Direct2D Device and Device Context now!
	ThrowIfFailed(DX::GetD2DFactory()->CreateDevice(_dxgiDevice.Get(), &_d2dDevice));
	ThrowIfFailed(_d2dDevice->CreateDeviceContext(D2D1_DEVICE_CONTEXT_OPTIONS_NONE, &_d2dDeviceContext));
}

void DirectWriteRenderer::Configure(ComPtr<IVirtualSurfaceImageSourceNative> source) {
	if(!_dxgiDevice) {
		InitializeDirect2D();
	}
	source->SetDevice(_dxgiDevice.Get());
}