#pragma once

#include "StructureNode.h"
#include "InlineNode.h"
#include "TextPointer.h"
#include "StructureVisitor.h"

namespace Prose {
	namespace Structure {
		namespace WFC = Windows::Foundation::Collections;

		private ref class BlockNode abstract :
			public StructureNode
		{
		public:
			virtual property WFC::IVector<InlineNode^>^ Inlines {
				WFC::IVector<InlineNode^>^ get() { return _inlines; }
			};

			virtual void Accept(StructureVisitor^ visitor) override;
			virtual BlockNode^ Clone(void) abstract;

		internal:
			BlockNode(void);

			TextPointer^ OffsetToPointer(UINT32 offset);

		private:
			WFC::IVector<InlineNode^>^ _inlines;
		};
	}
}