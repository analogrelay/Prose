#pragma once

#include "BaseNodes.h"

namespace Prose {
	namespace Controls {
		namespace WFM = Windows::Foundation::Metadata;
		namespace WUX = Windows::UI::Xaml;
		namespace WFC = Windows::Foundation::Collections;

		[WFM::WebHostHidden]
		[WUX::Markup::ContentProperty(Name = "Children")]
		public ref class Paragraph sealed :
			public Block
		{
		public:
			Paragraph(void);

			property WFC::IVector<Inline^>^ Children {
				WFC::IVector<Inline^>^ get() { return _children; }
			}

		internal:
			virtual Prose::Structure::BlockNode^ ConstructStructureNode(void) override;

		private:
			WFC::IVector<Inline^>^ _children;
		};
	}
}