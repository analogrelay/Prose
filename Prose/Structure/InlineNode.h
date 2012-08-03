#pragma once

#include "StructureNode.h"

namespace Prose {
	ref class TextFormat;

	namespace Structure {
		ref class InlinePair;
		ref class StructureVisitor;
		
		private ref class InlineNode abstract :
			public StructureNode
		{
		public:
			virtual property UINT32 Length { UINT32 get() abstract; }
			virtual InlinePair^ Split(UINT32 localOffset, TextFormat^ effectiveFormat) abstract;
			
			virtual void Accept(StructureVisitor^ visitor) override;
		internal:
			InlineNode(void) { }
		};
	}
}