#include "pch.h"
#include "Run.h"
#include "DocumentVisitor.h"

using namespace Prose::Structure;

Run::Run(void) : Inline() {}
Run::Run(Platform::String^ text) : Inline(), _text(text) {
}

void Run::Accept(DocumentVisitor^ visitor) {
	visitor->Visit(this);
}

InlinePair^ Run::Split(UINT32 localOffset) {
	if(localOffset == 0) {
		return ref new InlinePair(nullptr, this);
	} else if(localOffset >= Length) {
		return ref new InlinePair(this, nullptr);
	}
	
	std::wstring text(Text->Data());
	std::wstring leftStr = text.substr(0, localOffset);
	std::wstring rightStr = text.substr(localOffset);
	
	Run^ left = ref new Run(ref new Platform::String(leftStr.c_str()));
	Run^ right = ref new Run(ref new Platform::String(rightStr.c_str()));

	CopyStyleTo(left);
	CopyStyleTo(right);

	return ref new InlinePair(left, right);
}