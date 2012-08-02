#pragma once

#include "StructureNode.h"
#include "Paragraph.h"

namespace Prose {
	namespace Structure {
		namespace WUX = Windows::UI::Xaml;
		namespace WFC = Windows::Foundation::Collections;

		private ref class StructureTree :
			public StructureNode
		{
		public:
			virtual property WFC::IVector<Paragraph^>^ Paragraphs {
				WFC::IVector<Paragraph^>^ get() { return _paragraphs; }
			}

			virtual void Accept(StructureVisitor^ visitor) override;

		internal:
			StructureTree(void);

		private:
			WFC::IVector<Paragraph^>^ _paragraphs;
		};
	}
}