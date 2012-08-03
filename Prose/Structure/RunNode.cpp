#include "pch.h"
#include "RunNode.h"
#include "StructureVisitor.h"
#include "InlinePair.h"

using namespace Prose::Structure;

RunNode::RunNode(void) : InlineNode() {}
RunNode::RunNode(Platform::String^ text) : InlineNode(), _text(text) {
}

void RunNode::Accept(StructureVisitor^ visitor) {
	visitor->Visit(this);
}

InlinePair^ RunNode::Split(UINT32 localOffset) {
	if(localOffset == 0) {
		return ref new InlinePair(nullptr, this);
	} else if(localOffset >= Length) {
		return ref new InlinePair(this, nullptr);
	}
	
	std::wstring text(Text->Data());
	std::wstring leftStr = text.substr(0, localOffset);
	std::wstring rightStr = text.substr(localOffset);
	
	RunNode^ left = ref new RunNode(ref new Platform::String(leftStr.c_str()));
	RunNode^ right = ref new RunNode(ref new Platform::String(rightStr.c_str()));

	left->Format = Format->Clone();
	right->Format = Format->Clone();

	return ref new InlinePair(left, right);
}