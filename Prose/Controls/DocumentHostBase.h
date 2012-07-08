#pragma once

#include "..\Rendering\IRenderingPlan.h"
#include "..\Layout\LayoutTree.h"
#include "..\Structure\Document.h"

namespace Prose {
	namespace Controls {
		ref class DocumentHost;
		ref class OverflowDocumentHost;
		
		public ref class DocumentHostBase :
			public Windows::UI::Xaml::Controls::Panel
		{
		public:
			virtual property OverflowDocumentHost^ OverflowTarget {
				OverflowDocumentHost^ get();
				void set(OverflowDocumentHost^ value);
			};

			property bool HasOverflowContent {
				bool get() { return _hasOverflowContent; };
				void set(bool value) { _hasOverflowContent = value; };
			};
		protected:
			virtual Windows::Foundation::Size MeasureOverride(Windows::Foundation::Size) override;
			virtual Windows::Foundation::Size ArrangeOverride(Windows::Foundation::Size) override;

		private protected:
			DocumentHostBase(void);

			property DocumentHost^ RootHost {
				virtual DocumentHost^ get() { throw ref new Platform::NotImplementedException("RootHost must be implemented"); }
			};

			virtual Prose::Structure::Document^ GetDocument(void);

			void InvalidateDocument(void);
			void InvalidateRender(void);

			virtual void SendOverflow(void);

		private:
			Microsoft::WRL::WeakRef _targetRef;

			Windows::UI::Xaml::Media::Imaging::VirtualSurfaceImageSource^ _renderSurface;
			Windows::UI::Xaml::Controls::Image^ _renderHost;
			Prose::Layout::LayoutTree^ _layout;
			Prose::Rendering::IRenderingPlan^ _renderingPlan;
			Windows::Foundation::Size _layoutSize;
			Windows::Foundation::Collections::IVectorView<Prose::Structure::Paragraph^>^ _overflow;
			bool _hasOverflowContent;
			Windows::UI::Core::CoreCursor^ _oldCursor;

#ifdef _DEBUG
			Windows::UI::Xaml::Controls::Border^ _debugBorder;
#endif
			void Panel_PointerEntered(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ args);
			void Panel_PointerExited(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ args);

			void TargetChanged(void);
		};
	}
}