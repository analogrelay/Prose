#pragma once

#include <windows.ui.xaml.media.dxinterop.h>
#include "RenderingPlan.h"
#include "IDocumentRenderer.h"
#include "DirectWriteRenderingPlan.h"

#include "..\Layout\LayoutTree.h"
#include "..\Layout\LayoutVisitor.h"

namespace Prose {
	namespace Rendering {
		public ref class DirectWriteRenderer sealed :
			public IDocumentRenderer
		{
		public:
			DirectWriteRenderer(void);

			virtual RenderingPlan^ PlanRendering(Prose::Layout::LayoutTree^ layout);

			virtual void Render(RenderingPlan^ plan, Windows::UI::Xaml::Media::Imaging::SurfaceImageSource^ targetSurface, Windows::Foundation::Rect region);
		private:
			void InitializeDirect2D(void);
			void RenderPlan(DirectWriteRenderingPlan^ plan, Microsoft::WRL::ComPtr<ID2D1RenderTarget> target);

			Windows::UI::Xaml::Media::Imaging::SurfaceImageSource^ _knownTargetSurface;
			Microsoft::WRL::ComPtr<ISurfaceImageSourceNative> _targetSurface;
			
			Microsoft::WRL::ComPtr<IDXGIDevice> _dxgiDevice;
			Microsoft::WRL::ComPtr<ID2D1Device> _d2dDevice;
			Microsoft::WRL::ComPtr<ID2D1DeviceContext> _d2dDeviceContext;
		};
	}
}