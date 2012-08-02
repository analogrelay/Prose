#pragma once

#include "StructureNode.h"

namespace Prose {
	ref class TextFormat;

	namespace Structure {
		ref class InlinePair;
		ref class StructureVisitor;
		
		private ref class Inline abstract :
			public StructureNode
		{
		public:
			virtual property UINT32 Length { UINT32 get() FAUX_ABSTRACT }
			virtual InlinePair^ Split(UINT32 localOffset) FAUX_ABSTRACT;
			
			virtual void Accept(StructureVisitor^ visitor) override;
		internal:
			Inline(void) { }
		};
	}
}