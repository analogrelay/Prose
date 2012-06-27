#include <limits>

#include "pch.h"
#include "DocumentHost.h"

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;

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

Size DocumentHost::MeasureOverride(Size availableSize) {
	if(!_renderHost) {
		_renderHost = ref new Image();
	} 
	if(Children->Size != 1 || Children->GetAt(0) != _renderHost) {
		Children->Clear();
		Children->Append(_renderHost);
	}

	return availableSize;
}

Size DocumentHost::ArrangeOverride(Size finalSize) {
	_renderHost->Arrange(
		RectHelper::FromCoordinatesAndDimensions(
			0, 0, 
			finalSize.Width, finalSize.Height));
	return finalSize;
}

void DocumentHost::InvalidateDocument() {
	InvalidateMeasure();
	UpdateLayout();
	InvalidateRender();
}

void DocumentHost::InvalidateRender() {
	// Render the document
	_renderingPlan = Renderer->PlanRendering(_layout);

	// Render the plan
	_renderingPlan->RenderTo(_renderHost);
}

void DocumentHost::RendererChanged(DependencyObject^ sender, DependencyPropertyChangedEventArgs^ args) {
	DocumentHost^ host = (DocumentHost^)sender;
	host->InvalidateRender();
}

void DocumentHost::LayoutChanged(DependencyObject^ sender, DependencyPropertyChangedEventArgs^ args) {
	DocumentHost^ host = (DocumentHost^)sender;
	host->InvalidateDocument();
}