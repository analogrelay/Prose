#pragma once
#include "Layout\ILayoutEngine.h"
#include "Layout\LayoutTree.h"
#include "Rendering\IDocumentRenderer.h"
#include "Nodes\Document.h"

#include "DocumentHostBase.h"

namespace Prose {
	namespace Controls {
		namespace WFM = Windows::Foundation::Metadata;
		namespace WUX = Windows::UI::Xaml;
		namespace PR = Prose::Rendering;
		namespace PL = Prose::Layout;

		[WFM::WebHostHidden]
		[WUX::Markup::ContentProperty(Name = "Document")]
		public ref class DocumentHost sealed :
			public DocumentHostBase
		{
			DEPENDENCY_PROPERTY(TextStyle^, BaseStyle);
			DEPENDENCY_PROPERTY(Controls::Document^, Document);
			
		public:
			DocumentHost(void);

		public protected:
			virtual property DocumentHost^ RootHost {
				DocumentHost^ get() override { return this; }
			}

		internal:
			property PR::IDocumentRenderer^ Renderer {
				PR::IDocumentRenderer^ get() { return _renderer; }
			}

			property PL::ILayoutEngine^ LayoutEngine {
				PL::ILayoutEngine^ get() { return _layoutEngine; }
			}

			virtual TextStyle^ GetBaseStyle() override { return BaseStyle; }

		private:
			PR::IDocumentRenderer^ _renderer;
			PL::ILayoutEngine^ _layoutEngine;

			static void LayoutChanged(WUX::DependencyObject^ sender, WUX::DependencyPropertyChangedEventArgs^ args);
		};
	}
}