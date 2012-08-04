//
// DocumentViewer.h
// Declaration of the DocumentViewer class.
//
#pragma once

#include "OverflowDocumentHost.h"
#include "Nodes\Document.h"
#include "Nodes\BaseNodes.h"

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
			DEPENDENCY_PROPERTY(TextStyle^, BaseStyle);
			DEPENDENCY_PROPERTY(Controls::Document^, Document);
			DEPENDENCY_PROPERTY(WUX::DataTemplate^, OverflowTemplate);
			DEPENDENCY_PROPERTY(WUX::DataTemplate^, HostTemplate);
			DEPENDENCY_PROPERTY(double, ColumnWidth);
			
		public:
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

			static void DocumentChanged(WUX::DependencyObject^ sender, WUX::DependencyPropertyChangedEventArgs^ args);
		};
	}
}
