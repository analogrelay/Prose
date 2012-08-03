#pragma once

#include "StructureNode.h"
#include "Inline.h"
#include "TextPointer.h"
#include "StructureVisitor.h"

namespace Prose {
	namespace Structure {
		namespace WFC = Windows::Foundation::Collections;

		private ref class Block abstract :
			public StructureNode
		{
		public:
			virtual property WFC::IVector<Inline^>^ Inlines {
				WFC::IVector<Inline^>^ get() { return _inlines; }
			};

			virtual void Accept(StructureVisitor^ visitor) override;
			virtual Block^ Clone(void) abstract;

		internal:
			Block(void);

			TextPointer^ OffsetToPointer(UINT32 offset);

		private:
			WFC::IVector<Inline^>^ _inlines;
		};
	}
}