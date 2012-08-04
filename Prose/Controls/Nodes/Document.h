#pragma once

#include "Structure\StructureTree.h"
#include "BaseNodes.h"

namespace Prose {
	namespace Controls {
		namespace WFM = Windows::Foundation::Metadata;
		namespace WUX = Windows::UI::Xaml;
		namespace WFC = Windows::Foundation::Collections;

		[WFM::WebHostHidden]
		[WUX::Markup::ContentProperty(Name = "Children")]
		public ref class Document sealed :
			public Stylable
		{
		public:
			Document(void);

			property WFC::IVector<Block^>^ Children {
				WFC::IVector<Block^>^ get() { return _children; }
			}

		internal:
			Prose::Structure::StructureTree^ CreateStructureTree();

		private:
			WFC::IVector<Block^>^ _children;
		};
	}
}