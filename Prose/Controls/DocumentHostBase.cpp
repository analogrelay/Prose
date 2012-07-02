#include "pch.h"

#include "DocumentHost.h"
#include "OverflowDocumentHost.h"

using namespace Platform;
using namespace Platform::Collections;

using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;

using namespace Windows::UI::Core;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Input;
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

DocumentHostBase::DocumentHostBase() {
	PointerEntered += ref new PointerEventHandler(this, &DocumentHostBase::Panel_PointerEntered);
	PointerExited += ref new PointerEventHandler(this, &DocumentHostBase::Panel_PointerExited);
}

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

	_layoutSize = result->LayoutSize;
	return _layoutSize;
}

Size DocumentHostBase::ArrangeOverride(Size finalSize) {
	if(!RootHost) { return finalSize; }

	if(!_renderSurface) {
		_renderSurface = ref new VirtualSurfaceImageSource(0, 0, /* isOpaque */ false);
		_renderHost->Source = _renderSurface;
	}

	InvalidateRender();

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

void DocumentHostBase::InvalidateRender() {
	// Render the document
	_renderingPlan = RootHost->Renderer->PlanRendering(_layout);

	auto renderSize = _renderingPlan->RenderSize;

	// Render the plan
	RootHost->Renderer->Render(
		_renderingPlan, 
		_renderSurface, 
		RectHelper::FromCoordinatesAndDimensions(
			0,
			0,
			renderSize.Width,
			renderSize.Height));
}

void DocumentHostBase::Panel_PointerEntered(Object^ sender, PointerRoutedEventArgs^ args) {
	_oldCursor = Window::Current->CoreWindow->PointerCursor;
	Window::Current->CoreWindow->PointerCursor = ref new CoreCursor(
		CoreCursorType::IBeam, 1);
}

void DocumentHostBase::Panel_PointerExited(Object^ sender, PointerRoutedEventArgs^ args) {
	Window::Current->CoreWindow->PointerCursor = _oldCursor;
}