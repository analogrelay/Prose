#pragma once

#include "..\Structure\Document.h"

namespace Prose {
	namespace Controls {
		ref class DocumentHost;
		ref class OverflowDocumentHost;
		
		public ref class DocumentHostBase :
			public Windows::UI::Xaml::Controls::Panel
		{
		public:
			static property Windows::UI::Xaml::DependencyProperty^ OverflowTargetProperty {
				Windows::UI::Xaml::DependencyProperty^ get() { return _OverflowTargetProperty; };
			};

			virtual property OverflowDocumentHost^ OverflowTarget {
				OverflowDocumentHost^ get() { return (OverflowDocumentHost^)GetValue(OverflowTargetProperty); };
				void set(OverflowDocumentHost^ value) { SetValue(OverflowTargetProperty, value); };
			};

			property bool HasOverflowContent {
				bool get() { return _hasOverflowContent; };
				void set(bool value) { _hasOverflowContent = value; };
			};

		protected:
			property DocumentHost^ RootHost {
				virtual DocumentHost^ get() { throw ref new NotImplementedException("RootHost must be implemented"); }
			};

			virtual Prose::Structure::Document^ GetDocument(void);
			virtual Windows::Foundation::Size MeasureOverride(Windows::Foundation::Size availableSize) override;
			virtual Windows::Foundation::Size ArrangeOverride(Windows::Foundation::Size availableSize) override;

			void InvalidateDocument();
			void InvalidateRender(Windows::Foundation::Size finalSize);

			virtual void SendOverflow();

		private:
			Windows::UI::Xaml::Media::Imaging::SurfaceImageSource^ _renderSurface;
			Windows::UI::Xaml::Controls::Image^ _renderHost;
			Prose::Layout::LayoutTree^ _layout;
			Prose::Rendering::RenderingPlan^ _renderingPlan;
			Windows::Foundation::Size _layoutSize;
			Windows::Foundation::Collections::IVectorView<Prose::Structure::Paragraph^>^ _overflow;

			bool _hasOverflowContent;
			static Windows::UI::Xaml::DependencyProperty^ _OverflowTargetProperty;

			static void TargetChanged(Windows::UI::Xaml::DependencyObject^, Windows::UI::Xaml::DependencyPropertyChangedEventArgs^);
		};
	}
}