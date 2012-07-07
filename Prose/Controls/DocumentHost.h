#pragma once
#include "..\ObjectTracking.h"
#include "..\Layout\LayoutTree.h"
#include "..\Rendering\IDocumentRenderer.h"
#include "..\Structure\Document.h"

#include "DocumentHostBase.h"

namespace Prose {
	namespace Controls {
		[Windows::UI::Xaml::Markup::ContentProperty(Name = "Document")]
		public ref class DocumentHost sealed :
			public DocumentHostBase
		{
		public:
			static property Windows::UI::Xaml::DependencyProperty^ DocumentProperty {
				Windows::UI::Xaml::DependencyProperty^ get() { return _DocumentProperty; }
			};

			static property Windows::UI::Xaml::DependencyProperty^ RendererProperty {
				Windows::UI::Xaml::DependencyProperty^ get() { return _RendererProperty; }
			};

			static property Windows::UI::Xaml::DependencyProperty^ LayoutEngineProperty {
				Windows::UI::Xaml::DependencyProperty^ get() { return _LayoutEngineProperty; }
			};

			property Prose::Structure::Document^ Document {
				virtual Prose::Structure::Document^ get() { return (Prose::Structure::Document^)GetValue(DocumentProperty); }
				void set(Prose::Structure::Document^ value) { SetValue(DocumentProperty, value); }
			};

			property Prose::Rendering::IDocumentRenderer^ Renderer {
				virtual Prose::Rendering::IDocumentRenderer^ get() { return (Prose::Rendering::IDocumentRenderer^)GetValue(RendererProperty); }
				void set(Prose::Rendering::IDocumentRenderer^ value) { SetValue(RendererProperty, value); }
			};

			property Prose::Layout::ILayoutEngine^ LayoutEngine {
				virtual Prose::Layout::ILayoutEngine^ get() { return (Prose::Layout::ILayoutEngine^)GetValue(LayoutEngineProperty); }
				void set(Prose::Layout::ILayoutEngine^ value) { SetValue(LayoutEngineProperty, value); }
			};

			DocumentHost(void);
			~DocumentHost(void) { TrackDestruction(L"DocumentHost"); }

		public protected:
			virtual property DocumentHost^ RootHost {
				DocumentHost^ get() override { return this; }
			}

		private:
			TrackingId;

			static Windows::UI::Xaml::DependencyProperty^ _DocumentProperty;
			static Windows::UI::Xaml::DependencyProperty^ _RendererProperty;
			static Windows::UI::Xaml::DependencyProperty^ _LayoutEngineProperty;
			static void RendererChanged(Windows::UI::Xaml::DependencyObject^ sender, Windows::UI::Xaml::DependencyPropertyChangedEventArgs^ args);
			static void LayoutChanged(Windows::UI::Xaml::DependencyObject^ sender, Windows::UI::Xaml::DependencyPropertyChangedEventArgs^ args);
		};
	}
}