#include <limits>

#include "pch.h"
#include "DocumentHost.h"

#include "..\Rendering\DirectWriteRenderer.h"
#include "..\Layout\DirectWriteLayoutEngine.h"

using namespace Platform;
using namespace Platform::Collections;

using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Media::Imaging;

using namespace Prose::Controls;
using namespace Prose::Structure;
using namespace Prose::Rendering;
using namespace Prose::Layout;

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
	Renderer = ref new DirectWriteRenderer();
	LayoutEngine = ref new DirectWriteLayoutEngine();
}

Size DocumentHost::MeasureOverride(Size availableSize) {
	if(!_renderHost) {
		_renderHost = ref new Image();
	} 
	if(Children->Size != 1 || Children->GetAt(0) != _renderHost) {
		Children->Clear();
		Children->Append(_renderHost);
	}

	// Layout the document
	LayoutResult^ result = LayoutEngine->CreateLayout(this->Document, availableSize);

	if(result->Overflow->Size > 0) {
		// We has an overflow!
		SendOverflow(result->Overflow);
	}
	_layout = result->Layout;

	// Calculate overflow
	float usedHeight = 0.0;
	auto overflow = ref new Vector<LayoutBox^>();
	bool overflowing = false;
	for(UINT32 i = 0; i < _layout->Boxes->Size; i++) {
		auto box = _layout->Boxes->GetAt(i);
		if(overflowing) {
			overflow->Append(box);
		} else {
			// Will this node overflow?
			if(box->Metrics->Size.Height + usedHeight > availableSize.Height) {
				// Split the box
				
			} else {
				usedHeight += box->Metrics->Size.Height;
			}
		}
	}

	_renderSurface = ref new SurfaceImageSource(
		(int)(std::ceil(availableSize.Width)),
		(int)(std::ceil(availableSize.Height)),
		/* isOpaque */ false);
	InvalidateRender(availableSize);

	_renderHost->Source = _renderSurface;

	return availableSize;
}

Size DocumentHost::ArrangeOverride(Size finalSize) {
	_renderHost->Arrange(
		RectHelper::FromCoordinatesAndDimensions(
			0, 0, 
			finalSize.Width, finalSize.Height));
	return finalSize;
}

void DocumentHost::SendOverflow(IVectorView<Paragraph^>^ overflow) {
	if(OverflowTarget) {
		OverflowTarget->RecieveOverflow(overflow);
	}
}

void DocumentHost::InvalidateDocument() {
	InvalidateMeasure();
	UpdateLayout();
}

void DocumentHost::InvalidateRender(Size size) {
	// Render the document
	_renderingPlan = Renderer->PlanRendering(_layout);

	// Render the plan
	Renderer->Render(
		_renderingPlan, 
		_renderSurface, 
		RectHelper::FromCoordinatesAndDimensions(
			0,
			0,
			size.Width,
			size.Height));
}

void DocumentHost::RendererChanged(DependencyObject^ sender, DependencyPropertyChangedEventArgs^ args) {
	DocumentHost^ host = (DocumentHost^)sender;
	host->InvalidateArrange();
}

void DocumentHost::LayoutChanged(DependencyObject^ sender, DependencyPropertyChangedEventArgs^ args) {
	DocumentHost^ host = (DocumentHost^)sender;
	host->InvalidateDocument();
}