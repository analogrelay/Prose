#pragma once
#include <windows.ui.xaml.media.dxinterop.h>

#include "DirectWriteRenderer.h"
#include "DirectWriteSurface.h"

namespace Prose {
	namespace Rendering {
		namespace MW = Microsoft::WRL;

		class VirtualSurfaceCallbackThunk;

		private ref class DirectWriteRenderingPlan sealed :
			public IRenderingPlan
		{
		public:
			property Windows::Foundation::Collections::IVector<DirectWriteSurface^>^ Surfaces {
				Windows::Foundation::Collections::IVector<DirectWriteSurface^>^ get() { return _surfaces; }
			};

			virtual property Windows::Foundation::Size RenderSize {
				Windows::Foundation::Size get();
			}

			DirectWriteRenderingPlan(DirectWriteRenderer^ renderer);
			virtual ~DirectWriteRenderingPlan(void);

			virtual void Attach(Windows::UI::Xaml::Media::Imaging::VirtualSurfaceImageSource^ targetSurface, Windows::Foundation::Rect region);

		internal:
			void UpdatesNeeded(void);
			
		private:
			TrackingId;

			MW::ComPtr<VirtualSurfaceCallbackThunk> _thunk;
			MW::ComPtr<IVirtualSurfaceImageSourceNative> _surface;

			bool _attached;
			bool _renderSizeCalculated;

			DirectWriteRenderer^ _renderer;
			Windows::Foundation::Size _renderSize;
			Windows::Foundation::Collections::IVector<DirectWriteSurface^>^ _surfaces;

			void RenderSurface(DirectWriteSurface^ surface, MW::ComPtr<ID2D1RenderTarget> renderTarget, MW::ComPtr<ID2D1SolidColorBrush> brush);
		};

		private class VirtualSurfaceCallbackThunk :
			public IVirtualSurfaceUpdatesCallbackNative
		{
		public:
			VirtualSurfaceCallbackThunk(void) : _refCount(0) { TrackCreation(L"VirtualSurfaceCallbackThunk"); }
			~VirtualSurfaceCallbackThunk(void) { TrackDestruction(L"VirtualSurfaceCallbackThunk"); }

			void STDMETHODCALLTYPE Initialize(DirectWriteRenderingPlan^ plan)
			{
				MW::AsWeak(reinterpret_cast<IInspectable*>(plan), &_planRef);
			}

			virtual HRESULT STDMETHODCALLTYPE UpdatesNeeded(void) {
				try {
					MW::ComPtr<IInspectable> raw(nullptr);
					_planRef.As(&raw);
					(reinterpret_cast<DirectWriteRenderingPlan^>(raw.Get()))->UpdatesNeeded();
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
			TrackingId;

			MW::WeakRef _planRef;
			
			volatile UINT32 _refCount;
		};
	}
}