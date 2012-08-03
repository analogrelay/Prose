#pragma once

#include "Block.h"

namespace Prose {
	namespace Structure {
		private ref class Paragraph :
			public Block
		{
		public:
			virtual void Accept(StructureVisitor^ visitor) override;
			virtual Block^ Clone(void) override;

		internal:
			Paragraph(void);
		};
	}
}