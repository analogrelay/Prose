//
// DocumentViewer.h
// Declaration of the DocumentViewer class.
//
#pragma once

#include "OverflowDocumentHost.h"

#include <forward_list>

namespace Prose {
	namespace Controls {
		[Windows::UI::Xaml::Markup::ContentProperty(Name = "Document")]
		public ref class DocumentViewer sealed : 
			public Windows::UI::Xaml::Controls::Panel
		{
		public:
			static property Windows::UI::Xaml::DependencyProperty^ DocumentProperty {
				Windows::UI::Xaml::DependencyProperty^ get() { return _DocumentProperty; }
			};

			static property Windows::UI::Xaml::DependencyProperty^ OverflowTemplateProperty {
				Windows::UI::Xaml::DependencyProperty^ get() { return _OverflowTemplateProperty; }
			}

			static property Windows::UI::Xaml::DependencyProperty^ HostTemplateProperty {
				Windows::UI::Xaml::DependencyProperty^ get() { return _HostTemplateProperty; }
			}

			static property Windows::UI::Xaml::DependencyProperty^ ColumnWidthProperty {
				Windows::UI::Xaml::DependencyProperty^ get() { return _ColumnWidthProperty; }
			}

			property Prose::Structure::Document^ Document {
				virtual Prose::Structure::Document^ get() { return (Prose::Structure::Document^)GetValue(DocumentProperty); }
				void set(Prose::Structure::Document^ value) { SetValue(DocumentProperty, value); }
			};

			property Windows::UI::Xaml::DataTemplate^ OverflowTemplate {
				Windows::UI::Xaml::DataTemplate^ get() { return (Windows::UI::Xaml::DataTemplate^)GetValue(OverflowTemplateProperty); }
				void set(Windows::UI::Xaml::DataTemplate^ value) { SetValue(OverflowTemplateProperty, value); }
			};

			property Windows::UI::Xaml::DataTemplate^ HostTemplate {
				Windows::UI::Xaml::DataTemplate^ get() { return (Windows::UI::Xaml::DataTemplate^)GetValue(HostTemplateProperty); }
				void set(Windows::UI::Xaml::DataTemplate^ value) { SetValue(HostTemplateProperty, value); }
			};

			property double ColumnWidth {
				double get() { return (double)GetValue(ColumnWidthProperty); }
				void set(double value) { SetValue(ColumnWidthProperty, value); }
			};

			DocumentViewer();

		protected:
			virtual Windows::Foundation::Size MeasureOverride(Windows::Foundation::Size) override;
			virtual Windows::Foundation::Size ArrangeOverride(Windows::Foundation::Size) override;

		private:
			void InitializeHost(void);
			void CalculateOverflow(void);
			OverflowDocumentHost^ CreateOverflow(void);

			std::vector<OverflowDocumentHost^> _overflows;
			DocumentHost^ _root;

			static Windows::UI::Xaml::DependencyProperty^ _ColumnWidthProperty;
			static Windows::UI::Xaml::DependencyProperty^ _HostTemplateProperty;
			static Windows::UI::Xaml::DependencyProperty^ _DocumentProperty;
			static Windows::UI::Xaml::DependencyProperty^ _OverflowTemplateProperty;

			static void DocumentChanged(Windows::UI::Xaml::DependencyObject^ sender, Windows::UI::Xaml::DependencyPropertyChangedEventArgs^ args);
		};
	}
}
