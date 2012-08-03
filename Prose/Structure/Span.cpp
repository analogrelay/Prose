#include "pch.h"
#include "Span.h"
#include "StructureVisitor.h"
#include "..\ChildNodeCollection.h"
#include "InlinePair.h"

using namespace Prose::Structure;

using namespace Platform::Collections;

Span::Span(void) : _inlines(ref new Vector<Inline^>()) {}

void Span::Accept(StructureVisitor^ visitor) {
	visitor->Visit(this);
};

UINT32 Span::Length::get() {
	UINT32 sum = 0;
	for each(auto inl in Inlines) {
		sum += inl->Length;
	}
	return sum;
};

InlinePair^ Span::Split(UINT32 localOffset) {
	Span^ left = Clone();
	Span^ right = Clone();
	
	left->Format = Format->Clone();
	right->Format = Format->Clone();
	
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
			InlinePair^ subsplit = inl->Split(localOffset - offset);
			left->Inlines->Append(subsplit->Left);
			right->Inlines->Append(subsplit->Right);
		}
		offset += inl->Length;
	}

	return ref new InlinePair(left, right);
}