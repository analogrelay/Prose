#include "pch.h"
#include "StructureNode.h"
#include "Events\RoutedEventManager.h"

using namespace Prose::Structure;
using namespace Prose::Events;

using namespace Windows::UI::Xaml::Input;

StructureNode::StructureNode(void) : _eventManager(ref new RoutedEventManager()) {
}