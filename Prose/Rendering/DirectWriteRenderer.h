#pragma once

#include <windows.ui.xaml.media.dxinterop.h>

#include "IRenderingPlan.h"
#include "IDocumentRenderer.h"
#include "..\ObjectTracking.h"

#include "..\Layout\LayoutTree.h"
#include "..\Layout\LayoutVisitor.h"

namespace Prose {
	namespace Rendering {
		private ref class DirectWriteRenderer sealed :
			public IDocumentRenderer
		{
		public:
			DirectWriteRenderer(void);

			virtual IRenderingPlan^ PlanRendering(Prose::Layout::LayoutTree^ layout);

		internal:
			// Broken in RC :(
			/*property Microsoft::WRL::ComPtr<IDXGIDevice> Device {
				Microsoft::WRL::ComPtr<IDXGIDevice> get();
			}*/
			void Configure(Microsoft::WRL::ComPtr<IVirtualSurfaceImageSourceNative> source);

		private:
			void InitializeDirect2D(void);

			Microsoft::WRL::ComPtr<ID3D11Device> _d3d11Device;
			Microsoft::WRL::ComPtr<ID3D11DeviceContext> _deviceContext;
			Microsoft::WRL::ComPtr<IDXGIDevice> _dxgiDevice;
			Microsoft::WRL::ComPtr<ID2D1Device> _d2dDevice;
			Microsoft::WRL::ComPtr<ID2D1DeviceContext> _d2dDeviceContext;
		};
	}
}