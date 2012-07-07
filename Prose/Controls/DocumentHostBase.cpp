#include "pch.h"

#ifdef TRACE_RENDER
#include "..\Rendering\DirectWriteRenderingPlan.h"
#endif

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

#ifdef SHOW_DOCUMENTHOST_BORDERS
	if(!_debugBorder) {
		_debugBorder = ref new Border();
		Windows::UI::Color c = Windows::UI::Colors::HotPink;
		_debugBorder->BorderBrush = ref new Windows::UI::Xaml::Media::SolidColorBrush(c);
		_debugBorder->BorderThickness = ThicknessHelper::FromUniformLength(5);
		Children->Append(_debugBorder);
	}
	_debugBorder->Measure(availableSize);
#endif

	if(!_renderHost) {
		_renderHost = ref new Image();
		Children->Append(_renderHost);
	}

	// Layout the document
	LayoutResult^ result = RootHost->LayoutEngine->CreateLayout(GetDocument(), availableSize);

	_layoutSize = result->LayoutSize;

#ifdef TRACE_LAYOUT
	dbgf(L"Layout Complete - (%f x %f). Overflow Nodes: %u", _layoutSize.Width, _layoutSize.Height, result->Overflow->Size);
	for(UINT32 i = 0; i < result->Layout->Boxes->Size; i++) {
		auto box = result->Layout->Boxes->GetAt(i);
		std::wstring content = L"<empty>";
		if(box->Spans->Size > 0) {
			std::wstring str(box->Spans->GetAt(0)->Text->Data());
			if(str.length() > 15) {
				content = str.substr(0, 15) + std::wstring(L"...");
			} else {
				content = str;
			}
		}
		dbgf(L"\tIncluded (%f x %f). Content: '%s'", box->Metrics->Size.Width, box->Metrics->Size.Height, content.c_str());
	}
	for(UINT32 i = 0; i < result->Overflow->Size; i++) {
		auto para = result->Overflow->GetAt(i);
		std::wstring content = L"<empty>";
		if(para->Runs->Size > 0) {
			std::wstring str(para->Runs->GetAt(0)->Text->Data());
			if(str.length() > 15) {
				content = str.substr(0, 15) + std::wstring(L"...");
			} else {
				content = str;
			}
		}
		dbgf(L"\tOverflowed: '%s'", content.c_str());
	}
#endif

	if(result->Overflow->Size > 0) {
		// We has an overflow!
		HasOverflowContent = true;
		_overflow = result->Overflow;
		SendOverflow();
	}
	_layout = result->Layout;

	return _layoutSize;
}

Size DocumentHostBase::ArrangeOverride(Size finalSize) {
	if(!RootHost) { return finalSize; }

	if(!_renderSurface) {
		_renderSurface = ref new VirtualSurfaceImageSource(0, 0, /* isOpaque */ false);
		_renderHost->Source = _renderSurface;
	}

	InvalidateRender();

	Rect finalRect = RectHelper::FromCoordinatesAndDimensions(
		0, 0, 
		finalSize.Width, finalSize.Height);

#ifdef SHOW_DOCUMENTHOST_BORDERS
	_debugBorder->Arrange(finalRect);
#endif

	_renderHost->Arrange(finalRect);

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

#ifdef TRACE_RENDER
	dbgf(L"Rendering Plan Constructed (%f x %f): ", renderSize.Width, renderSize.Height);
	auto plan = (safe_cast<Prose::Rendering::DirectWriteRenderingPlan^>(_renderingPlan));
	for(UINT32 i = 0; i < plan->Surfaces->Size; i++) {
		auto surface = plan->Surfaces->GetAt(i);
		dbgf(L"\tSurface (x=%f,y=%f, %f x %f)", surface->Region.Left, surface->Region.Top, surface->Region.Width, surface->Region.Height);
	}
#endif

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