#pragma once

#include "BlockNode.h"

namespace Prose {
	namespace Structure {
		private ref class ParagraphNode :
			public BlockNode
		{
		public:
			virtual void Accept(StructureVisitor^ visitor) override;
			virtual BlockNode^ Clone(void) override;

		internal:
			ParagraphNode(void);
		};
	}
}