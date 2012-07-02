#pragma once

#include <windows.ui.xaml.media.dxinterop.h>

#include "IRenderingPlan.h"
#include "IDocumentRenderer.h"
#include "DirectWriteRenderingPlan.h"

#include "..\Layout\LayoutTree.h"
#include "..\Layout\LayoutVisitor.h"

namespace Prose {
	namespace Rendering {
		class VirtualSurfaceCallbackThunk;

		public ref class DirectWriteRenderer sealed :
			public IDocumentRenderer
		{
		public:
			DirectWriteRenderer(void);

			virtual IRenderingPlan^ PlanRendering(Prose::Layout::LayoutTree^ layout);

			virtual void Render(IRenderingPlan^ plan, Windows::UI::Xaml::Media::Imaging::VirtualSurfaceImageSource^ targetSurface, Windows::Foundation::Rect region);
		internal:
			void UpdatesNeeded(DirectWriteRenderingPlan^ plan);

		private:
			void InitializeDirect2D(void);
			void RenderSurface(DirectWriteSurface^ surface, Microsoft::WRL::ComPtr<ID2D1RenderTarget> renderTarget, Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> brush);

			Windows::UI::Xaml::Media::Imaging::VirtualSurfaceImageSource^ _knownTargetSurface;
			Microsoft::WRL::ComPtr<IVirtualSurfaceImageSourceNative> _targetSurface;

			Microsoft::WRL::ComPtr<VirtualSurfaceCallbackThunk> _thunk;
			Microsoft::WRL::ComPtr<IDXGIDevice> _dxgiDevice;
			Microsoft::WRL::ComPtr<ID2D1Device> _d2dDevice;
			Microsoft::WRL::ComPtr<ID2D1DeviceContext> _d2dDeviceContext;
		};

		private class VirtualSurfaceCallbackThunk :
			public IVirtualSurfaceUpdatesCallbackNative
		{
		public:
			void STDMETHODCALLTYPE Initialize(DirectWriteRenderer^ renderer, DirectWriteRenderingPlan^ plan) {
				_renderer = renderer;
				_plan = plan;
			}

			virtual HRESULT STDMETHODCALLTYPE UpdatesNeeded(void) {
				try {
					_renderer->UpdatesNeeded(_plan);
				} catch(Platform::Exception^ ex) {
					return ex->HResult;
				}
				return S_OK;
			}

			virtual HRESULT STDMETHODCALLTYPE QueryInterface( 
                /* [in] */ REFIID riid,
                /* [iid_is][out] */ _COM_Outptr_ void __RPC_FAR *__RPC_FAR *ppvObject) override {
				if(riid == IID_IUnknown || riid == __uuidof(IVirtualSurfaceUpdatesCallbackNative)) {
					*ppvObject = this;
					AddRef();
					return S_OK;
				}
				return E_NOINTERFACE;
			}

            virtual ULONG STDMETHODCALLTYPE AddRef(void) override {
				return static_cast<ULONG>(InterlockedIncrement(&_refCount));
			}

            virtual ULONG STDMETHODCALLTYPE Release( void) override {
				ULONG newCount = static_cast<ULONG>(InterlockedDecrement(&_refCount));
				if(newCount == 0) {
					delete this;
				}
				return newCount;
			}

		private:
			DirectWriteRenderer^ _renderer;
			DirectWriteRenderingPlan^ _plan;

			volatile UINT32 _refCount;
		};
	}
}