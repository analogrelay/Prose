#include "pch.h"
#include "DocumentNode.h"

using namespace Prose::Structure;
using namespace Prose::Events;

using namespace Windows::UI::Xaml::Input;

void DocumentNode::FirePointerEntered(PointerTextEventArgs^ args) {
	PointerEntered(this, args);
}