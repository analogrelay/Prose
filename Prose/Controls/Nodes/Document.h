#pragma once

#include "..\Structure\StructureTree.h"
#include "DocumentNode.h"
#include "IDocumentControl.h"

namespace Prose {
	namespace Controls {
		namespace WUX = Windows::UI::Xaml;
		namespace WFC = Windows::Foundation::Collections;

		[WUX::Markup::ContentProperty(Name = "Children")]
		public ref class Document sealed :
			public DocumentNode
		{
		public:
			property WFC::IVector<IDocumentControl^>^ Children {
				WFC::IVector<IDocumentControl^>^ get() { return _children; }
			}

		internal:
			Prose::Structure::StructureTree^ CreateStructure();

		private:
			WFC::IVector<IDocumentControl^>^ _children;
		};
	}
}