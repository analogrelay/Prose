#include "pch.h"
#include "DirectWriteLayoutEngine.h"
#include "DWLayoutMetrics.h"

#include <sstream>

using namespace Prose::Structure;
using namespace Prose::Layout;

using namespace Windows::Foundation;
using namespace Windows::UI::Xaml;

using namespace Microsoft::WRL;

LayoutResult^ DirectWriteLayoutEngine::CreateLayout(Document^ document, Windows::Foundation::Size layoutSize) {
	auto visitor = ref new LayoutEngineVisitor(layoutSize);
	document->Accept(visitor);
	return visitor->CreateResult();
}

LayoutEngineVisitor::LayoutEngineVisitor(Windows::Foundation::Size layoutSize) : 
	_layout(ref new LayoutTree()), 
	_overflow(ref new Vector<Paragraph^>()),
	_layoutSize(layoutSize),
	_width(0),
	_height(0) {
}

LayoutResult^ LayoutEngineVisitor::CreateResult() {
	return ref new LayoutResult(_layout, _overflow->GetView());
}

Point CalculatePosition(LayoutBox^ box, double yOffset) {
	// Apply margins
	double x = 0 + box->Margin.Left;
	double y = yOffset + box->Margin.Top;
	return PointHelper::FromCoordinates((float)x, (float)y);
}

void LayoutEngineVisitor::CalculateLayout(LayoutBox^ box, Paragraph^ paragraph) {
	// Calculate Position
	Point offset = CalculatePosition(box, _height);

	// TODO: Apply padding.

	// Collect ALL THE TEXT!
	std::wstringstream strm;
	for(UINT32 i = 0; i < box->Spans->Size; i++) {
		auto span = box->Spans->GetAt(i);
		std::wstring spanText = span->Text->Data();
		strm << spanText;
	}
	std::wstring str = strm.str();

	// Build a Text Format
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

	// Build a Text Layout
	ComPtr<IDWriteTextLayout> layout;
	ThrowIfFailed(DX::GetDWFactory()->CreateTextLayout(
		str.c_str(),
		str.length(),
		format.Get(),
		width,
		height,
		&layout));

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

		// Now carve up the string
		std::wstring keepString = str.substr(0, textOffset);
		std::wstring overflowString = str.substr(textOffset);

		// Reformat the kept string
		ThrowIfFailed(DX::GetDWFactory()->CreateTextLayout(
			keepString.c_str(),
			keepString.length(),
			format.Get(),
			width,
			height,
			&layout));
		ThrowIfFailed(layout->GetMetrics(&metrics));

		// Duplicate this box and put the rest of the string there
		auto newPara = paragraph->Clone();
		newPara->Runs->Append(ref new Run(ref new Platform::String(overflowString.c_str())));
		
		// Put the new box in the overflow set and start overflowing
		_overflow->Append(newPara);
		_overflowing = true;
	}

	Size measuredSize = SizeHelper::FromDimensions(metrics.width, metrics.height);

	// Apply bottom margin to get new layout height
	_height += (measuredSize.Height + vertical);

	// Apply right margin and get the max with layout width to get new layout width
	_width = max(_width, measuredSize.Width + horiz);

	// Apply these metrics to the box
	box->Metrics = ref new DWLayoutMetrics(layout, metrics, offset, measuredSize);
}

void LayoutEngineVisitor::Visit(Paragraph^ paragraph) {
	// Create a box for this paragraph
	_currentBox = ref new LayoutBox();

	// Give it the default style
	_currentBox->Margin = ThicknessHelper::FromUniformLength(10);

	// TODO: Apply user styles!

	// Visit children
	DocumentVisitor::Visit(paragraph);

	// Check overflow
	if(_overflowing) {
	}

	// Now calculate layout for this box
	CalculateLayout(_currentBox, paragraph);

	// Collect the newly constructed node
	_layout->Boxes->Append(_currentBox);
	_currentBox = nullptr;
}

void LayoutEngineVisitor::Visit(Run^ run) {
	// Create an span for this run
	Span^ span = ref new Span(run->Text);

	// And just collect it
	_currentBox->Spans->Append(span);
}