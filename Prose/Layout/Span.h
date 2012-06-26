#pragma once
#include "..\Structure\DocumentNode.h"
#include "LayoutNode.h"

namespace Prose {
	namespace Layout {
		public ref class Span sealed :
			public LayoutNode
		{
		public:
			Span(void);
			Span(Platform::String^);

			property Platform::String^ Text;
			
			virtual void Accept(LayoutVisitor^ visitor) override;
		};
	}
}