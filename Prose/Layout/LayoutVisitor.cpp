#include "pch.h"
#include "LayoutVisitor.h"

using namespace Prose::Layout;
using namespace Windows::Foundation::Collections;

void LayoutVisitor::Visit(LayoutTree^ tree) {
	VisitChildren<LayoutBox>(tree->Boxes);
}

void LayoutVisitor::Visit(LayoutBox^ box) {
}

template<typename T>
void LayoutVisitor::VisitChildren(IIterable<T^>^ nodes) {
	for each(T^ node in nodes) {
		node->Accept(this);
	}
}