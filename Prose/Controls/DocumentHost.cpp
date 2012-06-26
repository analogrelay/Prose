#include <limits>

#include "pch.h"
#include "DocumentHost.h"

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::UI::Xaml;

using namespace Prose::Controls;
using namespace Prose::Structure;
using namespace Prose::Rendering;

DependencyProperty^ DocumentHost::_DocumentProperty = DependencyProperty::Register(
	L"Document", Document::typeid, DocumentHost::typeid, ref new PropertyMetadata(
		nullptr, ref new PropertyChangedCallback(DocumentHost::LayoutChanged)));
DependencyProperty^ DocumentHost::_RendererProperty = DependencyProperty::Register(
	L"Renderer", IDocumentRenderer::typeid, DocumentHost::typeid, ref new PropertyMetadata(
		nullptr, ref new PropertyChangedCallback(DocumentHost::RendererChanged)));
DependencyProperty^ DocumentHost::_LayoutEngineProperty = DependencyProperty::Register(
	L"LayoutEngine", IDocumentRenderer::typeid, DocumentHost::typeid, ref new PropertyMetadata(
		nullptr, ref new PropertyChangedCallback(DocumentHost::LayoutChanged)));

DocumentHost::DocumentHost(void) {
}

void DocumentHost::InvalidateDocument() {
}

void DocumentHost::InvalidateRender() {
}

Size DocumentHost::MeasureOverride(Size availableSize) {
	// Set up variables
	float usedWidth = 0.0;
	float usedHeight = 0.0;

	for(UINT32 i = 0; i < Children->Size; i++) {
		auto child = Children->GetAt(i);

		//// First, give it all the height in the world!
		//child->Measure(SizeHelper::FromDimensions(availableSize.Width, std::numeric_limits<float>::infinity()));
		//auto desired = child->DesiredSize;

		// Now, be more reasonable and give it the remaining height
		child->Measure(SizeHelper::FromDimensions(availableSize.Width, availableSize.Height - usedHeight));
		auto minimum = child->DesiredSize;

		// Reserve space for it
		usedHeight += minimum.Height;
		usedWidth = max(minimum.Width, usedWidth);
	}
	return SizeHelper::FromDimensions(usedWidth, usedHeight);
}

Size DocumentHost::ArrangeOverride(Size availableSize) {
	// Set up variables
	float width = 0.0;
	float yOffset = 0.0;

	for(UINT32 i = 0; i < Children->Size; i++) {
		auto child = Children->GetAt(i);

		// Build the final rectangle
		auto finalRect = RectHelper::FromLocationAndSize(
			PointHelper::FromCoordinates(0, yOffset),
			SizeHelper::FromDimensions(child->DesiredSize.Width, child->DesiredSize.Height));

		// Move the current y-offset and width record
		yOffset += finalRect.Height;
		width = max(finalRect.Width, width);

		// Arrange the child
		child->Arrange(finalRect);
	}
	return SizeHelper::FromDimensions(width, yOffset);
}

void DocumentHost::RendererChanged(DependencyObject^ sender, DependencyPropertyChangedEventArgs^ args) {
	DocumentHost^ host = (DocumentHost^)sender;
	host->InvalidateRender();
}

void DocumentHost::LayoutChanged(DependencyObject^ sender, DependencyPropertyChangedEventArgs^ args) {
	DocumentHost^ host = (DocumentHost^)sender;
	host->InvalidateDocument();
}