//
// DocumentViewer.h
// Declaration of the DocumentViewer class.
//
#pragma once

#include "OverflowDocumentHost.h"
#include "Nodes\Document.h"

#include <forward_list>

namespace Prose {
	namespace Controls {
		namespace WFM = Windows::Foundation::Metadata;
		namespace WUX = Windows::UI::Xaml;

		[WFM::WebHostHidden]
		[WUX::Markup::ContentProperty(Name = "Document")]
		public ref class DocumentViewer sealed : 
			public WUX::Controls::Panel
		{
		public:
			static property WUX::DependencyProperty^ DocumentProperty {
				WUX::DependencyProperty^ get() { return _DocumentProperty; }
			};

			static property WUX::DependencyProperty^ OverflowTemplateProperty {
				WUX::DependencyProperty^ get() { return _OverflowTemplateProperty; }
			}

			static property WUX::DependencyProperty^ HostTemplateProperty {
				WUX::DependencyProperty^ get() { return _HostTemplateProperty; }
			}

			static property WUX::DependencyProperty^ ColumnWidthProperty {
				WUX::DependencyProperty^ get() { return _ColumnWidthProperty; }
			}

			property Controls::Document^ Document {
				virtual Controls::Document^ get() { return (Controls::Document^)GetValue(DocumentProperty); }
				void set(Controls::Document^ value) { SetValue(DocumentProperty, value); }
			};

			property WUX::DataTemplate^ OverflowTemplate {
				WUX::DataTemplate^ get() { return (WUX::DataTemplate^)GetValue(OverflowTemplateProperty); }
				void set(WUX::DataTemplate^ value) { SetValue(OverflowTemplateProperty, value); }
			};

			property WUX::DataTemplate^ HostTemplate {
				WUX::DataTemplate^ get() { return (WUX::DataTemplate^)GetValue(HostTemplateProperty); }
				void set(WUX::DataTemplate^ value) { SetValue(HostTemplateProperty, value); }
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
			void RelayoutDocument(void);
			OverflowDocumentHost^ CreateOverflow(void);

			std::vector<OverflowDocumentHost^> _overflows;
			DocumentHost^ _root;

			static WUX::DependencyProperty^ _ColumnWidthProperty;
			static WUX::DependencyProperty^ _HostTemplateProperty;
			static WUX::DependencyProperty^ _DocumentProperty;
			static WUX::DependencyProperty^ _OverflowTemplateProperty;

			static void DocumentChanged(WUX::DependencyObject^ sender, WUX::DependencyPropertyChangedEventArgs^ args);
		};
	}
}
