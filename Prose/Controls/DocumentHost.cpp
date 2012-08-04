#include <limits>

#include "pch.h"
#include "ObjectTracking.h"
#include "DocumentHost.h"

#include "Rendering\DirectWriteRenderer.h"
#include "Layout\DirectWriteLayoutEngine.h"

using namespace Windows::UI::Xaml;

using namespace Prose;
using namespace Prose::Controls;
using namespace Prose::Structure;
using namespace Prose::Rendering;
using namespace Prose::Layout;

DependencyProperty^ DocumentHost::_BaseStyleProperty = RegisterDP("BaseStyle", TextStyle::typeid, DocumentHost::typeid);
DependencyProperty^ DocumentHost::_DocumentProperty = RegisterDP(
	"Document", Document::typeid, DocumentHost::typeid, DP_METADATA_WITH_HANDLER(nullptr, DocumentHost::LayoutChanged));

DocumentHost::DocumentHost(void) : _renderer(ref new DirectWriteRenderer()), _layoutEngine(ref new DirectWriteLayoutEngine()) {
	TrackCreation(L"DocumentHost");
}

void DocumentHost::LayoutChanged(DependencyObject^ sender, DependencyPropertyChangedEventArgs^ args) {
	DocumentHost^ host = (DocumentHost^)sender;
	host->InvalidateDocument();
}