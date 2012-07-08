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
LayoutBuilder::LayoutBuilder() : _offset(0), _formatters(), _deviceDependentFormatters(new std::vector<dd_format_operation_t>()), _buffer() { }

void LayoutBuilder::AddFormatter(format_action_t format, UINT32 start_position, UINT32 length) {
	format_operation_t op;
	op.action = format;
	op.start_position = start_position;
	op.length = length;

	_formatters.push_back(op);
}

void LayoutBuilder::Process(Run^ run) {
	UINT32 length = run->Text->Length();
	_buffer << run->Text->Data();
	ProcessInline(run, length);
	_offset += length;
}

void LayoutBuilder::ProcessInline(Inline^ inl, UINT32 length) {
	if(!_isnan(inl->FontSize)) {
		FLOAT fontSize = (FLOAT)inl->FontSize;
		AddFormatter([fontSize](ComPtr<IDWriteTextLayout> layout, DWRITE_TEXT_RANGE range) {
			ThrowIfFailed(layout->SetFontSize((FLOAT)fontSize, range));
		}, _offset, length);
	}
	if(inl->FontFamily != nullptr) {
		FontFamily^ family = inl->FontFamily;
		AddFormatter([family](ComPtr<IDWriteTextLayout> layout, DWRITE_TEXT_RANGE range) {
			layout->SetFontFamilyName(family->Source->Data(), range);
		}, _offset, length);
	}
	if(inl->Foreground != nullptr) {
		// Convert to a DirectWrite Brush Factory

	}
}

ComPtr<IDWriteTextLayout> LayoutBuilder::CreateLayout(ComPtr<IDWriteTextFormat> baseFormat, FLOAT boxWidth, FLOAT boxHeight) {
	ComPtr<IDWriteTextLayout> layout;
	std::wstring str = _buffer.str();
	ThrowIfFailed(DX::GetDWFactory()->CreateTextLayout(
		str.c_str(),
		str.length(),
		baseFormat.Get(),
		boxWidth,
		boxHeight,
		&layout));
	RunFormatters(layout, str.length());
	return layout;
}

std::wstring LayoutBuilder::Str() {
	return _buffer.str();
}

void LayoutBuilder::ApplyMetrics(DWLayoutMetrics^ metrics) {
	
}

ComPtr<IDWriteTextLayout> LayoutBuilder::Reformat(std::wstring newString, ComPtr<IDWriteTextFormat> baseFormat, FLOAT boxWidth, FLOAT boxHeight) {
	ComPtr<IDWriteTextLayout> layout;
	ThrowIfFailed(DX::GetDWFactory()->CreateTextLayout(
		newString.c_str(),
		newString.length(),
		baseFormat.Get(),
		boxWidth,
		boxHeight,
		&layout));
	RunFormatters(layout, newString.length());
	return layout;
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

bool LayoutEngineVisitor::CalculateLayout(LayoutBox^ box, Paragraph^ paragraph) {
	// Apply margins
	double x = box->Margin.Left;
	double y = _height + box->Margin.Top;
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
	float width = _layoutSize.Width - horiz;
	float height = 
		(_layoutSize.Height - _height) -
		vertical;

	if(width < 0 || height < 0) {
		if(_acceptedAtLeastOne) {
			_overflow->Append(paragraph);
			_overflowing = true;
			return false;
		} else {
			width = max(0, width);
			height = max(0, height);
		}
	}

	// Build the prepared text layout
	ComPtr<IDWriteTextLayout> layout = _builder->CreateLayout(format, width, height);

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
		std::wstring str = _builder->Str();
		std::wstring keepString = str.substr(0, ptr->GlobalOffset);

		if(keepString.length() == 0) {
			// Just drop this box
			return false;
		}
		else {
			// Reformat the kept string and continue
			layout = _builder->Reformat(keepString, format, width, height);
			ThrowIfFailed(layout->GetMetrics(&metrics));
		}
	}
	_acceptedAtLeastOne = true;

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

void LayoutEngineVisitor::Visit(Paragraph^ paragraph) {
	// Set up the builder and box
	LayoutBuilder* oldbuilder = _builder;
	LayoutBox^ oldbox = _currentBox;
	_currentBox = ref new LayoutBox();
	_builder = new LayoutBuilder();

	// Give it the default style
	_currentBox->Margin = ThicknessHelper::FromUniformLength(10);

	// TODO: Apply user styles!

	// Visit children
	DocumentVisitor::Visit(paragraph);

	// Check overflow
	if(_overflowing) {
		// Skip!
		_overflow->Append(paragraph);
	} else {
		// Now calculate layout for this box
		if(CalculateLayout(_currentBox, paragraph)) {
			// Collect the newly constructed node
			_layout->Boxes->Append(_currentBox);
			_currentBox = nullptr;
		}
	}

	// Clean up
	if(_builder) {
		delete _builder;
	}
	_builder = oldbuilder;
	_currentBox = oldbox;
}

void LayoutEngineVisitor::Visit(Run^ run) {
	_builder->Process(run);
}