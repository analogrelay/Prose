#include "pch.h"
#include "StructureVisitor.h"
#include "StructureTree.h"
#include "ParagraphNode.h"
#include "RunNode.h"
#include "SpanNode.h"

using namespace Prose::Structure;

using namespace Windows::Foundation::Collections;

void StructureVisitor::Visit(StructureNode^ node) {
}

void StructureVisitor::Visit(StructureTree^ tree) {
	Visit(static_cast<StructureNode^>(tree));
	for(auto node : tree->Blocks) {
		node->Accept(this);
	}
}

void StructureVisitor::Visit(BlockNode^ BlockNode) {
	Visit(static_cast<StructureNode^>(BlockNode));
	for(auto node : BlockNode->Inlines) {
		node->Accept(this);
	}
}

void StructureVisitor::Visit(SpanNode^ span) {
	Visit(static_cast<InlineNode^>(span));
	for each(InlineNode^ node in span->Inlines) {
		node->Accept(this);
	}
}

void StructureVisitor::Visit(ParagraphNode^ paragraph) {
	Visit(static_cast<BlockNode^>(paragraph));
}

void StructureVisitor::Visit(RunNode^ run) {
	Visit(static_cast<InlineNode^>(run));
}

void StructureVisitor::Visit(InlineNode^ inl) {
	Visit(static_cast<StructureNode^>(inl));
}