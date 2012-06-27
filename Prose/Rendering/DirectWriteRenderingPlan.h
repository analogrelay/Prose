#pragma once
#include <windows.ui.xaml.media.dxinterop.h>

#include "DirectWriteSurface.h"

namespace Prose {
	namespace Rendering {
		private ref class DirectWriteRenderingPlan sealed :
			public RenderingPlan
		{
		public:
			property Windows::Foundation::Collections::IVector<DirectWriteSurface^>^ Surfaces {
				Windows::Foundation::Collections::IVector<DirectWriteSurface^>^ get() { return _surfaces; }
			};

			DirectWriteRenderingPlan(void) : _surfaces(ref new Platform::Collections::Vector<DirectWriteSurface^>()) { }

			virtual void RenderTo(Windows::UI::Xaml::Media::Imaging::SurfaceImageSource^ targetSurface, Windows::Foundation::Rect targetRect) override;
		private:
			void InitializeDirect2D(void);

			Windows::UI::Xaml::Media::Imaging::SurfaceImageSource^ _knownTargetSurface;
			Microsoft::WRL::ComPtr<ISurfaceImageSourceNative> _targetSurface;
			
			Microsoft::WRL::ComPtr<IDXGIDevice> _dxgiDevice;
			Microsoft::WRL::ComPtr<ID2D1Device> _d2dDevice;
			Microsoft::WRL::ComPtr<ID2D1DeviceContext> _d2dDeviceContext;

			Windows::Foundation::Collections::IVector<DirectWriteSurface^>^ _surfaces;
		};
	}
}