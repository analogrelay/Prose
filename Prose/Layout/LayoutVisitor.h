#pragma once
#include "LayoutTree.h"
#include "LayoutBox.h"

namespace Prose {
	namespace Layout {
		public interface class ILayoutVisitor {
			void Visit(LayoutTree^ tree);
			void Visit(ILayoutBox^ box);
			void Visit(ILayoutInline^ span);
		};

		private ref class LayoutVisitor abstract
		{
		public:
			virtual void Visit(LayoutTree^ tree);
			virtual void Visit(ILayoutBox^ box);
			virtual void Visit(ILayoutInline^ span);
		private:
			template<typename T> void VisitChildren(Windows::Foundation::Collections::IIterable<T^>^ nodes);
		};
	}
}