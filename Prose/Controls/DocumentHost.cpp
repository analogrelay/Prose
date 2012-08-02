#include <limits>

#include "pch.h"
#include "..\ObjectTracking.h"
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

DocumentHost::DocumentHost(void) : _renderer(ref new DirectWriteRenderer()), _layoutEngine(ref new DirectWriteLayoutEngine()) {
	TrackCreation(L"DocumentHost");
}

void DocumentHost::LayoutChanged(DependencyObject^ sender, DependencyPropertyChangedEventArgs^ args) {
	DocumentHost^ host = (DocumentHost^)sender;
	host->InvalidateDocument();
}