#pragma once

#include "StructureNode.h"
#include "BlockNode.h"

namespace Prose {
	namespace Structure {
		namespace WUX = Windows::UI::Xaml;
		namespace WFC = Windows::Foundation::Collections;

		private ref class StructureTree :
			public StructureNode
		{
		public:
			virtual property WFC::IVector<BlockNode^>^ Blocks {
				WFC::IVector<BlockNode^>^ get() { return _blocks; }
			}

			virtual void Accept(StructureVisitor^ visitor) override;

		internal:
			StructureTree(void);

		private:
			WFC::IVector<BlockNode^>^ _blocks;
		};
	}
}