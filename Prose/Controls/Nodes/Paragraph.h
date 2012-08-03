#pragma once

#include "DocumentNode.h"

namespace Prose {
	namespace Controls {
		namespace WFM = Windows::Foundation::Metadata;
		namespace WUX = Windows::UI::Xaml;
		namespace WFC = Windows::Foundation::Collections;

		[WFM::WebHostHidden]
		[WUX::Markup::ContentProperty(Name = "Children")]
		public ref class Paragraph sealed :
			public BlockNode
		{
		public:
			Paragraph(void);

			property WFC::IVector<InlineNode^>^ Children {
				WFC::IVector<InlineNode^>^ get() { return _children; }
			}

		internal:
			Prose::Structure::StructureTree^ CreateStructureTree();

		private:
			WFC::IVector<InlineNode^>^ _children;
		};
	}
}