#pragma once
#include "LayoutTree.h"
#include "LayoutBox.h"

namespace Prose {
	namespace Layout {
		namespace WFC = Windows::Foundation::Collections;

		private ref class LayoutVisitor abstract
		{
		public:
			virtual void Visit(LayoutTree^ tree);
			virtual void Visit(LayoutBox^ box);
			virtual void Visit(LayoutInline^ span);
		private:
			template<typename T> void VisitChildren(WFC::IIterable<T^>^ nodes);
		};
	}
}