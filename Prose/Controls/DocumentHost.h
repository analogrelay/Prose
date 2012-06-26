#pragma once
#include "..\Layout\LayoutTree.h"
#include "..\Rendering\IDocumentRenderer.h"
#include "..\Structure\Document.h"
#include "IDocumentSource.h"
#include "DocumentHostBase.h"

namespace Prose {
	namespace Controls {
		[Windows::UI::Xaml::Markup::ContentProperty(Name = "Document")]
		public ref class DocumentHost sealed :
			public DocumentHostBase,
			public IDocumentSource
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

			virtual property OverflowDocumentHost^ OverflowTarget {
				OverflowDocumentHost^ get() override { return (OverflowDocumentHost^)GetValue(OverflowTargetProperty); }
				void set(OverflowDocumentHost^ value) override { SetValue(OverflowTargetProperty, value); }
			};

			DocumentHost(void);

		protected:
			virtual Windows::Foundation::Size MeasureOverride(Windows::Foundation::Size availableSize) override;
			virtual Windows::Foundation::Size ArrangeOverride(Windows::Foundation::Size availableSize) override;

		private:
			Prose::Layout::LayoutTree^ _layout;

			void InvalidateDocument();
			void InvalidateRender();

			static Windows::UI::Xaml::DependencyProperty^ _DocumentProperty;
			static Windows::UI::Xaml::DependencyProperty^ _RendererProperty;
			static Windows::UI::Xaml::DependencyProperty^ _LayoutEngineProperty;
			static void RendererChanged(Windows::UI::Xaml::DependencyObject^ sender, Windows::UI::Xaml::DependencyPropertyChangedEventArgs^ args);
			static void LayoutChanged(Windows::UI::Xaml::DependencyObject^ sender, Windows::UI::Xaml::DependencyPropertyChangedEventArgs^ args);
		};
	}
}