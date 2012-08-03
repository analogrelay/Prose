#include "pch.h"
#include "SpanNode.h"
#include "StructureVisitor.h"
#include "ChildNodeCollection.h"
#include "InlinePair.h"

using namespace Prose;
using namespace Prose::Structure;

using namespace Platform::Collections;

SpanNode::SpanNode(void) : _inlines(ref new Vector<InlineNode^>()) {}

void SpanNode::Accept(StructureVisitor^ visitor) {
	visitor->Visit(this);
};

UINT32 SpanNode::Length::get() {
	UINT32 sum = 0;
	for each(auto inl in Inlines) {
		sum += inl->Length;
	}
	return sum;
};

InlinePair^ SpanNode::Split(UINT32 localOffset, TextFormat^ effectiveFormat) {
	SpanNode^ left = ref new SpanNode();
	SpanNode^ right = ref new SpanNode();
	
	left->Format = effectiveFormat;
	right->Format = effectiveFormat;
	
	UINT32 offset = 0;
	for(UINT32 i = 0; i < Inlines->Size; i++) {
		auto inl = Inlines->GetAt(i);
		if(offset >= localOffset) {
			right->Inlines->Append(inl);
		}
		else if((offset + inl->Length) < localOffset) {
			left->Inlines->Append(inl);
		} else {
			// Recursive split
			InlinePair^ subsplit = inl->Split(localOffset - offset, effectiveFormat);
			left->Inlines->Append(subsplit->Left);
			right->Inlines->Append(subsplit->Right);
		}
		offset += inl->Length;
	}

	return ref new InlinePair(left, right);
}