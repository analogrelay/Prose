#include "pch.h"

#include "DocumentHost.h"
#include "OverflowDocumentHost.h"

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

DependencyProperty^ DocumentHostBase::_OverflowTargetProperty = DependencyProperty::Register(
	L"OverflowTarget",
	OverflowDocumentHost::typeid, 
	DocumentHostBase::typeid,
	ref new PropertyMetadata(nullptr, ref new PropertyChangedCallback(DocumentHostBase::TargetChanged)));

void DocumentHostBase::TargetChanged(DependencyObject^ sender, DependencyPropertyChangedEventArgs^ args) {
	DocumentHostBase^ host = (DocumentHostBase^)sender;
	host->SendOverflow();
}

Document^ DocumentHostBase::GetDocument() {
	return RootHost->Document;
}

Size DocumentHostBase::MeasureOverride(Size availableSize) {
	if(!RootHost) { return availableSize; }

	if(!_renderHost) {
		_renderHost = ref new Image();
	} 
	if(Children->Size != 1 || Children->GetAt(0) != _renderHost) {
		Children->Clear();
		Children->Append(_renderHost);
	}

	// Layout the document
	LayoutResult^ result = RootHost->LayoutEngine->CreateLayout(GetDocument(), availableSize);

	if(result->Overflow->Size > 0) {
		// We has an overflow!
		HasOverflowContent = true;
		_overflow = result->Overflow;
		SendOverflow();
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

Size DocumentHostBase::ArrangeOverride(Size finalSize) {
	if(!RootHost) { return finalSize; }

	_renderHost->Arrange(
		RectHelper::FromCoordinatesAndDimensions(
			0, 0, 
			finalSize.Width, finalSize.Height));
	return finalSize;
}

void DocumentHostBase::SendOverflow() {
	if(OverflowTarget && _overflow) {
		OverflowTarget->RecieveOverflow(RootHost, _overflow);
		_overflow = nullptr;
	}
}

void DocumentHostBase::InvalidateDocument() {
	InvalidateMeasure();
	UpdateLayout();
}

void DocumentHostBase::InvalidateRender(Size size) {
	// Render the document
	_renderingPlan = RootHost->Renderer->PlanRendering(_layout);

	// Render the plan
	RootHost->Renderer->Render(
		_renderingPlan, 
		_renderSurface, 
		RectHelper::FromCoordinatesAndDimensions(
			0,
			0,
			size.Width,
			size.Height));
}

