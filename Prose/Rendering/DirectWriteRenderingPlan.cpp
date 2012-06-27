#include "pch.h"
#include "DirectWriteRenderingPlan.h"

using namespace Platform;
using namespace Prose::Rendering;
using namespace Windows::UI::Xaml::Media::Imaging;
using namespace Microsoft::WRL;

void DirectWriteRenderingPlan::RenderTo(SurfaceImageSource^ targetSurface, Windows::Foundation::Rect targetRect) {
	if(_knownTargetSurface == nullptr || !Object::ReferenceEquals(targetSurface, _knownTargetSurface)) {
		IInspectable* insp = reinterpret_cast<IInspectable*>(targetSurface);
		ThrowIfFailed(insp->QueryInterface(__uuidof(ISurfaceImageSourceNative), &_targetSurface));

		// Set up Direct2D Context
		InitializeDirect2D();

		// Set the device on the surface
		_targetSurface->SetDevice(_dxgiDevice.Get());
	}

	RECT target;
	DX::ToNativeRect(targetRect, &target);

	ComPtr<IDXGISurface> surface;
	POINT offset;
	ThrowIfFailed(_targetSurface->BeginDraw(target, &surface, &offset));

	This is where I am!
}

void DirectWriteRenderingPlan::InitializeDirect2D() {
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