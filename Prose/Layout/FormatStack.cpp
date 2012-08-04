#include "pch.h"
#include "FormatStack.h"

using namespace Prose;
using namespace Prose::Layout;

FormatStack::FormatStack(void) : _stack(), _baseFormat(nullptr) { }
FormatStack::FormatStack(TextFormat^ baseFormat) : _stack(), _baseFormat(baseFormat) { }

void FormatStack::PushFormat(TextFormat^ format) {
	_stack.push_back(format);
}

TextFormat^ FormatStack::CalculateCurrentFormat(TextFormat^ inputFormat) {
	auto base = TextFormat::MergeSequence(_stack);
	if(_baseFormat) {
		base = _baseFormat->MergeWith(base);
	}
	auto format = inputFormat;
	if(base) {
		format = base->MergeWith(format);
	}
	return format;
}

void FormatStack::PopFormat(void) {
	_stack.pop_back();
}