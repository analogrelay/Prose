#pragma once
#include "Box.h"

namespace Prose {
	namespace Layout {
		public ref class LayoutVisitor abstract
		{
		public:
			virtual void Visit(Box^ box);
			virtual void Visit(Span^ span);
			virtual void Visit(LayoutTree^ tree);

		private:
			template<typename T> void VisitChildren(Windows::Foundation::Collections::IIterable<T^>^ nodes);
		};
	}
}