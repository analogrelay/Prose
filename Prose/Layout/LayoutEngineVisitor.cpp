#include "pch.h"
#include "LayoutResult.h"
#include "LayoutEngineVisitor.h"
#include "DWLayoutMetrics.h"

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
LayoutBuilder::LayoutBuilder(LayoutBox^ box, Windows::Foundation::Collections::IVector<Prose::Structure::Paragraph^>^ overflow) : 
	_offset(0), _formatters(), _buffer(), _box(box), _overflow(overflow) { }

void LayoutBuilder::Process(Run^ run) {
	UINT32 length = run->Text->Length();
	_buffer << run->Text->Data();
	ProcessInline(run, length);
	_offset += length;
}

void LayoutBuilder::ProcessInline(Inline^ inl, UINT32 length) {
	TextFormat^ format = ref new TextFormat();
	bool appliedSomething = false;
	if(!_isnan(inl->FontSize)) {
		appliedSomething = true;
		format->FontSize = inl->FontSize;
	}
	if(inl->FontFamily != nullptr) {
		appliedSomething = true;
		format->FontFamily = inl->FontFamily;
	}
	if(inl->Foreground != nullptr) {
		appliedSomething = true;
		format->Foreground = inl->Foreground;
	}
	if(appliedSomething) {
		
	}
}

layout_t LayoutBuilder::CreateLayout(LayoutBox^ box, Paragraph^ paragraph, bool requireAtLeastOne, float boxWidth, float boxHeight, float yOffset) {
	layout_t layoutResult;
	layoutResult.success = false;
	layoutResult.overflowing = false;

	// Apply margins
	double x = box->Margin.Left;
	double y = yOffset + box->Margin.Top;
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
	float horiz = ((float)box->Margin.Left + (float)box->Margin.Right);
	float vertical = ((float)box->Margin.Top + (float)box->Margin.Bottom);
	float width = boxWidth - horiz;
	float height = boxHeight - vertical;

	if(width < 0 || height < 0) {
		if(!requireAtLeastOne) {
			_overflow->Append(paragraph);
			layoutResult.overflowing = true;
			return layoutResult;
		} else {
			width = max(0, width);
			height = max(0, height);
		}
	}

	// Build the prepared text layout
	ComPtr<IDWriteTextLayout> layout = CreateLayout(format, _buffer.str(), width, height);

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
		TextPointer^ ptr = paragraph->OffsetToPointer(textOffset);
		
		// Split that node
		InlinePair^ pair = ptr->Node->Split(ptr->LocalOffset);
		
		// Collect the split node and all nodes after into a new paragraph
		Paragraph^ overflowParagraph = ref new Paragraph();
		overflowParagraph->Inlines->Append(pair->Right);
		for(UINT32 i = (ptr->NodeIndex + 1); i < paragraph->Inlines->Size; i++) {
			overflowParagraph->Inlines->Append(paragraph->Inlines->GetAt(i));
		}

		// Put the new paragraph in the overflow set and start overflowing
		_overflow->Append(overflowParagraph);
		_overflowing = true;

		// Calculate the string to keep in this node
		std::wstring str = _buffer.str();
		std::wstring keepString = str.substr(0, ptr->GlobalOffset);

		if(keepString.length() == 0) {
			// Just drop this box
			return false;
		}
		else {
			// Reformat the kept string and continue
			layout = CreateLayout(format, keepString, width, height);
			ThrowIfFailed(layout->GetMetrics(&metrics));
		}
	}
	
	Size measuredSize = SizeHelper::FromDimensions(metrics.widthIncludingTrailingWhitespace, metrics.height);

	// Apply top margin to get new layout height
	_height += (measuredSize.Height + vertical);

	// Apply left margin and get the max with layout width to get new layout width
	_width = max(_width, measuredSize.Width + horiz);

	// Determine box sizes
	Rect renderArea = RectHelper::FromLocationAndSize(origin, measuredSize);
	Rect layoutBounds = RectHelper::FromCoordinatesAndDimensions(
		0, _width, measuredSize.Width + horiz, measuredSize.Height + vertical);

	// Apply these metrics to the box
	box->Metrics = ref new DWLayoutMetrics(layout, metrics, renderArea, layoutBounds);
	return true;
}

void LayoutBuilder::RunFormatters(ComPtr<IDWriteTextLayout> layout, UINT32 length) {
	for(auto formatter : _formatters) {
		if(formatter.start_position < length) {
			// Create the range
			DWRITE_TEXT_RANGE range;
			range.startPosition = formatter.start_position;
			range.length = min(formatter.length, (length - formatter.start_position));

			// Run the formatter
			formatter.action(layout, range);
		}
	}
}

ComPtr<IDWriteTextLayout> LayoutBuilder::ConstructLayout(

LayoutEngineVisitor::LayoutEngineVisitor(Windows::Foundation::Size layoutSize) : 
	_layout(ref new LayoutTree()), 
	_overflow(ref new Vector<Paragraph^>()),
	_layoutSize(layoutSize),
	_width(0),
	_height(0),
	_acceptedAtLeastOne(false) {
}

LayoutResult^ LayoutEngineVisitor::CreateResult() {
	return ref new LayoutResult(_layout, _overflow->GetView());
}

void LayoutEngineVisitor::Visit(Paragraph^ paragraph) {
	// If we're overflowing, just add this to overflow and stop
	if(_overflowing) {
		_overflow->Append(paragraph);
	}

	// Set up the layout builder
	LayoutBuilder* oldbuilder = _builder;
	_builder = new LayoutBuilder(_layoutSize, _width, _height, _overflow);

	// Visit children
	DocumentVisitor::Visit(paragraph);

	// Now perform layout for this box
	layout_outcome_t outcome = _builder->Layout();
	_overflowing = _overflowing || outcome.overflowing;
	if(outcome.successful) {
		// Reserve the space
		_height += outcome.size.Height;
		_width = max(_width, outcome.size.Width);

		// Collect the newly constructed node
		_layout->Boxes->Append(_currentBox);
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