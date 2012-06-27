#include "pch.h"
#include "DirectWriteLayoutEngine.h"
#include "DWLayoutMetrics.h"

#include <sstream>

using namespace Prose::Structure;
using namespace Prose::Layout;

using namespace Windows::Foundation;
using namespace Windows::UI::Xaml;

using namespace Microsoft::WRL;

LayoutTree^ DirectWriteLayoutEngine::CreateLayout(Document^ document, Windows::Foundation::Size layoutSize) {
	auto visitor = ref new LayoutEngineVisitor(layoutSize);
	document->Accept(visitor);
	return visitor->Layout;
}

void NoOpCollector(LayoutNode^ node) { }
layout_collector_t BoxCollector(Box^ box) {
	return [box](LayoutNode^ node) {
		box->Spans->Append(static_cast<Span^>(node));
	};
}
LayoutEngineVisitor::LayoutEngineVisitor(Windows::Foundation::Size layoutSize) : 
	_collector(NoOpCollector), 
	_layout(nullptr), 
	_layoutSize(layoutSize),
	_width(0),
	_height(0) { 
}

Point CalculatePosition(Box^ box, double yOffset) {
	// Apply margins
	double x = 0 + box->Margin.Left;
	double y = yOffset + box->Margin.Top;
	return PointHelper::FromCoordinates((float)x, (float)y);
}

void LayoutEngineVisitor::CalculateLayout(Box^ box) {
	// Calculate Position
	Point offset = CalculatePosition(box, _height);

	// TODO: Apply padding.

	// Collect ALL THE TEXT!
	std::wstringstream strm;
	for(UINT32 i = 0; i < box->Spans->Size; i++) {
		strm << box->Spans->GetAt(i)->Text->Data();
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
		12.0,
		L"en-US",
		&format));

	// Build a Text Layout
	ComPtr<IDWriteTextLayout> layout;
	ThrowIfFailed(DX::GetDWFactory()->CreateTextLayout(
		str.c_str(),
		str.length(),
		format.Get(),
		_layoutSize.Width,
		_layoutSize.Height,
		&layout));

	// Extract the measured size
	DWRITE_TEXT_METRICS metrics;
	ThrowIfFailed(layout->GetMetrics(&metrics));
	Size measuredSize = SizeHelper::FromDimensions(metrics.width, metrics.height);

	// Apply bottom margin to get new layout height
	_height = _height + measuredSize.Height + box->Margin.Bottom;

	// Apply right margin and get the max with layout width to get new layout width
	_width = max(_width, measuredSize.Width + offset.X + box->Margin.Right);

	// Apply these metrics to the box
	box->Metrics = ref new DWLayoutMetrics(layout, offset, measuredSize);
}

void LayoutEngineVisitor::Visit(Paragraph^ paragraph) {
	// Create a box for this paragraph
	Box^ box = ref new Box();

	// Give it the default style
	box->Margin = ThicknessHelper::FromUniformLength(10);

	// TODO: Apply user styles!

	// Set up the collector
	auto old = _collector;
	_collector = BoxCollector(box);

	// Visit children
	DocumentVisitor::Visit(paragraph);

	// Reset the collector
	_collector = old;

	// Now calculate layout for this box
	CalculateLayout(box);

	// Collect the newly constructed node
	_collector(box);
}

void LayoutEngineVisitor::Visit(Run^ run) {
	// Create an span for this run
	Span^ span = ref new Span(run->Text);

	// And just collect it
	_collector(span);
}