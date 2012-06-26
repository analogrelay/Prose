#include "pch.h"
#include "DocumentVisitor.h"

using namespace Prose::Structure;

using namespace Windows::Foundation::Collections;

void DocumentVisitor::Visit(Document^ document) {
	VisitChildren<Paragraph>(document->Paragraphs);
}

void DocumentVisitor::Visit(Paragraph^ paragraph) {
	VisitChildren<Run>(paragraph->Runs);
}

void DocumentVisitor::Visit(Run^ run) {
}

template<typename T>
void DocumentVisitor::VisitChildren(IIterable<T^>^ nodes) {
	for(T^ node : nodes) {
		node->Accept(this);
	}
}