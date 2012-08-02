#pragma once

#include "..\Rendering\IRenderingPlan.h"
#include "..\Layout\LayoutTree.h"
#include "..\Structure\Paragraph.h"
#include "Nodes\Document.h"

namespace Prose {
	namespace Controls {
		namespace WF = Windows::Foundation;
		namespace WFM = Windows::Foundation::Metadata;
		namespace WUX = Windows::UI::Xaml;
		
		namespace PL = Prose::Layout;
		namespace PS = Prose::Structure;

		ref class DocumentHost;
		ref class OverflowDocumentHost;
		
		[WFM::WebHostHidden]
		public ref class DocumentHostBase :
			public WUX::Controls::Panel
		{
		public:
			property OverflowDocumentHost^ OverflowTarget {
				OverflowDocumentHost^ get();
				void set(OverflowDocumentHost^ value);
			};

			property bool HasOverflowContent {
				bool get() { return _hasOverflowContent; };
				void set(bool value) { _hasOverflowContent = value; };
			};
		protected:
			virtual WF::Size MeasureOverride(WF::Size) override;
			virtual WF::Size ArrangeOverride(WF::Size) override;
			virtual void OnPointerEntered(Platform::Object^ sender, WUX::Input::PointerRoutedEventArgs^ args);
			virtual void OnPointerExited(Platform::Object^ sender, WUX::Input::PointerRoutedEventArgs^ args);
			/*virtual void OnPointerMoved(Platform::Object^ sender, WUX::Input::PointerRoutedEventArgs^ args);*/

		private protected:
			DocumentHostBase(void);

			property DocumentHost^ RootHost {
				virtual DocumentHost^ get() { throw ref new Platform::NotImplementedException("RootHost must be implemented"); }
			};

			virtual PS::StructureTree^ GetStructureTree(void);

			void InvalidateDocument(void);
			void InvalidateRender(void);

			virtual void SendOverflow(void);

		private:
			bool _hasOverflowContent;
			Microsoft::WRL::WeakRef _targetRef;
			PL::LayoutTree^ _layout;
			PL::LayoutNode^ _currentlySelected;
			Prose::Rendering::IRenderingPlan^ _renderingPlan;
			
			WUX::Media::Imaging::VirtualSurfaceImageSource^ _renderSurface;
			WUX::Controls::Image^ _renderHost;
			WF::Size _layoutSize;
			WF::Collections::IVectorView<PS::Paragraph^>^ _overflow;
			Windows::UI::Core::CoreCursor^ _oldCursor;

#ifdef _DEBUG
			WUX::Controls::Border^ _debugBorder;
#endif
			void TargetChanged(void);
		};
	}
}