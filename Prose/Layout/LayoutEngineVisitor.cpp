#include "pch.h"
#include "LayoutInline.h"
#include "LayoutResult.h"
#include "LayoutEngineVisitor.h"
#include "DWLayoutMetrics.h"

#include "Structure\RunNode.h"
#include "Structure\StructureTree.h"

using namespace Platform::Collections;

using namespace Prose;
using namespace Prose::Structure;
using namespace Prose::Layout;

using namespace Windows::Foundation;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Media;

using namespace Microsoft::WRL;

LayoutEngineVisitor::LayoutEngineVisitor(Windows::Foundation::Size layoutSize, TextFormat^ baseFormat) :
	_layout(ref new LayoutTree()),
	_overflow(ref new Vector<BlockNode^>()),
	_layoutSize(layoutSize),
	_width(0),
	_height(0),
	_canOverflowAll(false),
	_formatStack(ref new FormatStack(baseFormat)) {
}

LayoutResult^ LayoutEngineVisitor::CreateResult() {
	return ref new LayoutResult(_layout, _overflow->GetView());
}

void LayoutEngineVisitor::Visit(BlockNode^ paragraph) {
	// If we're overflowing, just add this to overflow and stop
	if(_overflowing) {
		AddOverflow(paragraph);
		return;
	}

	_formatStack->PushFormat(paragraph->Format);
	
	// Set up the layout builder
	LayoutBuilder* oldbuilder = _builder;
	auto box = ref new LayoutBox(paragraph, ThicknessHelper::FromLengths(0, 10, 10, 10));
	_builder = new LayoutBuilder(this, box, paragraph, _formatStack);

	// Visit children
	StructureVisitor::Visit(paragraph);

	// Now perform layout for this box
	if(_builder->Layout()) {
		// Collect the newly constructed node
		_layout->Boxes->Append(box);
	}

	// Clean up
	if(_builder) {
		delete _builder;
	}
	_builder = oldbuilder;

	_formatStack->PopFormat();
}

void LayoutEngineVisitor::Visit(StructureTree^ tree) {
	_formatStack->PushFormat(tree->Format);
	StructureVisitor::Visit(tree);
	_formatStack->PopFormat();
}

void LayoutEngineVisitor::Visit(RunNode^ run) {
	_builder->Process(run);
}

void LayoutEngineVisitor::Visit(SpanNode^ span) {
	_formatStack->PushFormat(span->Format);
	StructureVisitor::Visit(span);
	_formatStack->PopFormat();
}

Size LayoutEngineVisitor::GetAvailableSize() {
	return SizeHelper::FromDimensions(_layoutSize.Width, _layoutSize.Height - _height);
}

void LayoutEngineVisitor::AddOverflow(BlockNode^ BlockNode) {
	_overflowing = true;
	_overflow->Append(BlockNode);
}

void LayoutEngineVisitor::ReserveSpace(float width, float height) {
	_width = max(width, _width);
	_height += height;
}