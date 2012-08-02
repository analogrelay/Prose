#include "pch.h"
#include "..\Structure\InlinePair.h"
#include "LayoutInline.h"
#include "LayoutResult.h"
#include "LayoutEngineVisitor.h"
#include "DWLayoutMetrics.h"
#include "..\Structure\Run.h"

#include <sstream>

using namespace Platform::Collections;

using namespace Prose;
using namespace Prose::Structure;
using namespace Prose::Layout;

using namespace Windows::Foundation;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Media;

using namespace Microsoft::WRL;

// LayoutBuilder
LayoutBuilder::LayoutBuilder(LayoutEngineVisitor^ visitor, LayoutBox^ box, Prose::Structure::Paragraph^ paragraph) : 
	_offset(0), _formatters(ref new Vector<FormattedRange^>()), _buffer(), _box(box), _visitor(visitor), _paragraph(paragraph) { }

void LayoutBuilder::Process(Run^ run) {
	UINT32 length = run->Text->Length();
	_buffer << run->Text->Data();
	ProcessInline(run, length);
	_offset += length;

	LayoutInline^ linline = ref new LayoutInline(run, run->Text);
	_box->Inlines->Append(linline);
}

void LayoutBuilder::ProcessInline(Inline^ inl, UINT32 length) {
	TextFormat^ base = TextFormat::MergeSequence(_formatStack);
	TextFormat^ format = inl->Format;
	if(base) {
		format = base->MergeWith(inl->Format);
	}
	if(format) {
		_formatters->Append(
			ref new FormattedRange(
				ref new TextRange(_offset, length),
				inl->Format));
	}
}

void LayoutBuilder::PushFormat(TextFormat^ format) {
	_formatStack.push_back(format);
}

void LayoutBuilder::PopFormat() {
	_formatStack.pop_back();
}

bool LayoutBuilder::Layout() {
	if(!_box) {
		throw ref new Platform::FailureException("Invalid Operation: Cannot use layout builder twice");
	}

	// Apply margins
	double top = _visitor->VerticalOffset;
	double x = _box->Margin.Left;
	double y = top + _box->Margin.Top;
	Point origin = PointHelper::FromCoordinates((float)x, (float)y);

	// TODO: Apply padding.

	// Build the base Text Format
	ComPtr<IDWriteTextFormat> format;
	ThrowIfFailed(DX::GetDWFactory()->CreateTextFormat(
		L"Georgia",
		DX::GetSystemFonts().Get(),
		DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		58.0,
		L"en-US",
		&format));

	// Determine the layout box for this text
	auto available = _visitor->GetAvailableSize();
	float horiz = ((float)_box->Margin.Left + (float)_box->Margin.Right);
	float vertical = ((float)_box->Margin.Top + (float)_box->Margin.Bottom);
	float width = available.Width - horiz;
	float height = available.Height - vertical;

	if(width < 0 || height < 0) {
		if(!_visitor->CanOverflowAll) {
			_visitor->AddOverflow(_paragraph);
			_box = nullptr;
			return false;
		} else {
			width = max(0, width);
			height = max(0, height);
		}
	}

	// Build the prepared text layout
	std::wstring str = _buffer.str();
	UINT32 textLength = str.length();
	ComPtr<IDWriteTextLayout> layout = ConstructLayout(format, str, width, height);

	// Extract the measured size
	DWRITE_TEXT_METRICS metrics;
	ThrowIfFailed(layout->GetMetrics(&metrics));

	if(metrics.height > height) {
		// Too much text! For now, just mark the end of this box and drop the rest of the text.
		DWRITE_LINE_METRICS* lineMetrics = new DWRITE_LINE_METRICS[metrics.lineCount];
		UINT32 lineCount;
		ThrowIfFailed(layout->GetLineMetrics(lineMetrics, metrics.lineCount, &lineCount));

		// Find the line that's over the limit
		float usedHeight = 0.0;
		UINT32 textOffset = 0;
		for(UINT32 i = 0; i < lineCount && ((usedHeight + lineMetrics[i].height) < height); i++) {
			usedHeight += lineMetrics[i].height;
			textOffset += lineMetrics[i].length;
		}

		// Clean up
		delete [] lineMetrics;

		// Get a pointer to the split location
		TextPointer^ ptr = _paragraph->OffsetToPointer(textOffset);

		// Split that node
		InlinePair^ pair = ptr->Node->Split(ptr->LocalOffset);

		// Collect the split node and all nodes after into a new paragraph
		Paragraph^ overflowParagraph = ref new Paragraph();
		overflowParagraph->Inlines->Append(pair->Right);
		for(UINT32 i = (ptr->NodeIndex + 1); i < _paragraph->Inlines->Size; i++) {
			overflowParagraph->Inlines->Append(_paragraph->Inlines->GetAt(i));
		}

		// Put the new paragraph in the overflow set and start overflowing
		_visitor->AddOverflow(overflowParagraph);

		// Calculate the string to keep in this node
		std::wstring str = _buffer.str();
		std::wstring keepString = str.substr(0, ptr->GlobalOffset);
		textLength = keepString.length();
			
		if(keepString.length() == 0) {
			// Just drop this box
			_box = nullptr;
			return false;
		}
		else {
			// Reformat the kept string and continue
			layout = ConstructLayout(format, keepString, width, height);
			ThrowIfFailed(layout->GetMetrics(&metrics));
		}
	}

	Size measuredSize = SizeHelper::FromDimensions(metrics.widthIncludingTrailingWhitespace, metrics.height);

	// Apply top margin to get new layout height
	_visitor->ReserveSpace(measuredSize.Width + horiz, measuredSize.Height + vertical);

	// Determine box sizes
	Rect renderArea = RectHelper::FromLocationAndSize(origin, measuredSize);
	Rect layoutBounds = RectHelper::FromCoordinatesAndDimensions(
		0, (float)top, measuredSize.Width + horiz, measuredSize.Height + vertical);

	// Apply these metrics to the box
	_box->Metrics = ref new DWLayoutMetrics(layout, metrics, renderArea, layoutBounds, _formatters, textLength);

	_box = nullptr;
	return true;
}

void LayoutBuilder::ApplyFormatters(ComPtr<IDWriteTextLayout> layout, UINT32 length) {
	for(auto formatter : _formatters) {
		if(formatter->Range->Offset < length) {
			// Create the range
			UINT32 offset = formatter->Range->Offset;
			UINT32 range = min(formatter->Range->Length, (length - formatter->Range->Offset));

			// Run the formatter
			formatter->Format->ApplyDeviceIndependent(layout, offset, range);
		}
	}
}

ComPtr<IDWriteTextLayout> LayoutBuilder::ConstructLayout(ComPtr<IDWriteTextFormat> baseFormat, std::wstring text, float boxWidth, float boxHeight) {
	ComPtr<IDWriteTextLayout> layout;
	ThrowIfFailed(DX::GetDWFactory()->CreateTextLayout(
		text.c_str(),
		text.length(),
		baseFormat.Get(),
		boxWidth,
		boxHeight,
		&layout));
	ApplyFormatters(layout, text.length());
	return layout;
}

LayoutEngineVisitor::LayoutEngineVisitor(Windows::Foundation::Size layoutSize) : 
	_layout(ref new LayoutTree()), 
	_overflow(ref new Vector<Paragraph^>()),
	_layoutSize(layoutSize),
	_width(0),
	_height(0),
	_canOverflowAll(false) {
}

LayoutResult^ LayoutEngineVisitor::CreateResult() {
	return ref new LayoutResult(_layout, _overflow->GetView());
}

void LayoutEngineVisitor::Visit(Paragraph^ paragraph) {
	// If we're overflowing, just add this to overflow and stop
	if(_overflowing) {
		AddOverflow(paragraph);
		return;
	}

	// Set up the layout builder
	LayoutBuilder* oldbuilder = _builder;
	auto box = ref new LayoutBox(paragraph, ThicknessHelper::FromUniformLength(10));
	_builder = new LayoutBuilder(this, box, paragraph);

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
}

void LayoutEngineVisitor::Visit(Run^ run) {
	_builder->Process(run);
}

void LayoutEngineVisitor::Visit(SpanBase^ span) {
	_builder->PushFormat(span->Format);
	StructureVisitor::Visit(span);
	_builder->PopFormat();
}

Size LayoutEngineVisitor::GetAvailableSize() {
	return SizeHelper::FromDimensions(_layoutSize.Width, _layoutSize.Height - _height);
}

void LayoutEngineVisitor::AddOverflow(Paragraph^ paragraph) {
	_overflowing = true;
	_overflow->Append(paragraph);
}

void LayoutEngineVisitor::ReserveSpace(float width, float height) {
	_width = max(width, _width);
	_height += height;
}
