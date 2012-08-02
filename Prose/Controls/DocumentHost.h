#pragma once
#include "..\Layout\ILayoutEngine.h"
#include "..\Layout\LayoutTree.h"
#include "..\Rendering\IDocumentRenderer.h"
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
		public:
			static property WUX::DependencyProperty^ DocumentProperty {
				WUX::DependencyProperty^ get() { return _DocumentProperty; }
			};

			property Controls::Document^ Document {
				virtual Controls::Document^ get() { return (Controls::Document^)GetValue(DocumentProperty); }
				void set(Controls::Document^ value) { SetValue(DocumentProperty, value); }
			};

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

		private:
			PR::IDocumentRenderer^ _renderer;
			PL::ILayoutEngine^ _layoutEngine;

			static WUX::DependencyProperty^ _DocumentProperty;
			static void LayoutChanged(WUX::DependencyObject^ sender, WUX::DependencyPropertyChangedEventArgs^ args);
		};
	}
}