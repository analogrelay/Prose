#pragma once
#include "..\Structure\DocumentNode.h"

namespace Prose {
	namespace Layout {
		ref class LayoutVisitor;

		public ref class LayoutNode abstract
		{
		public:
			virtual void Accept(LayoutVisitor^ visitor) = 0;
		};
	}
}