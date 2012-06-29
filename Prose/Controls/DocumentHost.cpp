#include <limits>

#include "pch.h"
#include "DocumentHost.h"

#include "..\Rendering\DirectWriteRenderer.h"
#include "..\Layout\DirectWriteLayoutEngine.h"

using namespace Windows::UI::Xaml;

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

void DocumentHost::RendererChanged(DependencyObject^ sender, DependencyPropertyChangedEventArgs^ args) {
	DocumentHost^ host = (DocumentHost^)sender;
	host->InvalidateArrange();
}

void DocumentHost::LayoutChanged(DependencyObject^ sender, DependencyPropertyChangedEventArgs^ args) {
	DocumentHost^ host = (DocumentHost^)sender;
	host->InvalidateDocument();
}