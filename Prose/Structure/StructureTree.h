#pragma once

#include "StructureNode.h"
#include "Block.h"

namespace Prose {
	namespace Structure {
		namespace WUX = Windows::UI::Xaml;
		namespace WFC = Windows::Foundation::Collections;

		private ref class StructureTree :
			public StructureNode
		{
		public:
			virtual property WFC::IVector<Block^>^ Blocks {
				WFC::IVector<Block^>^ get() { return _blocks; }
			}

			virtual void Accept(StructureVisitor^ visitor) override;

		internal:
			StructureTree(void);

		private:
			WFC::IVector<Block^>^ _blocks;
		};
	}
}