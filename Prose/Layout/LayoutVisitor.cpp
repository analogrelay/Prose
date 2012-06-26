#include "pch.h"
#include "LayoutVisitor.h"

using namespace Prose::Layout;
using namespace Windows::Foundation::Collections;

void LayoutVisitor::Visit(LayoutTree^ tree) {
	VisitChildren<Box>(tree->Boxes);
}

void LayoutVisitor::Visit(Box^ box) {
	VisitChildren<Span>(box->Spans);
}

void LayoutVisitor::Visit(Span^ span) {
}

template<typename T>
void LayoutVisitor::VisitChildren(IIterable<T^>^ nodes) {
	for(T^ node : nodes) {
		node->Accept(this);
	}
}