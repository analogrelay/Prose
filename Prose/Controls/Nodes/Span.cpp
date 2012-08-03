#include "pch.h"
#include "Span.h"
#include "Structure\SpanNode.h"

using namespace Prose;
using namespace Prose::Controls;
using namespace Prose::Structure;

using namespace Windows::UI::Xaml;
using namespace Windows::UI::Text;

using namespace Platform::Collections;

SpanBase::SpanBase() : _children(ref new Vector<Inline^>()) { }

Italic::Italic() : SpanBase() { 
	FontStyle = ::FontStyle::Italic;
}

Bold::Bold() : SpanBase() { 
	FontWeight = ::FontWeights::Bold;
}

Underline::Underline() : SpanBase() { 
	HasUnderline = true;
}

InlineNode^ SpanBase::ConstructStructureNode() {
	auto span = ref new SpanNode();
	auto format = CreateFormat();
	span->Format = format;
	for(auto child : Children) {
		auto node = child->ConstructStructureNode();
		if(node) {
			span->Inlines->Append(node);
		}
	}
	return span;
}