#pragma once

#include "..\TextFormat.h"
#include "..\Events\PointerTextEvent.h"
#include "..\Events\IRoutedEventSource.h"
#include "..\Events\RoutedEvent.h"
#include "..\Events\CustomRoutedEvent.h"

namespace Prose {
	namespace Structure {
		namespace PE = Prose::Events;
		namespace WUX = Windows::UI::Xaml;

		ref class StructureVisitor;

		private ref class StructureNode abstract : 
			public WUX::DependencyObject,
			public PE::IRoutedEventSource
		{
		public:
			virtual property StructureNode^ Parent { StructureNode^ get() { return _parent; } }
			virtual property TextFormat^ Format;
			virtual void Accept(StructureVisitor^ visitor) abstract;
			
			virtual PE::IRoutedEventManager^ GetRoutedEventManager() { return _eventManager; }
			virtual PE::IRoutedEventSource^ GetEventRoutingParent(void) { return dynamic_cast<PE::IRoutedEventSource^>(Parent); }

			virtual void DetachParent(void) { _parent = nullptr; }
			virtual void AttachParent(StructureNode^ parent) { _parent = parent; }

		private protected:
			StructureNode(void);

		private:
			StructureNode^ _parent;
			PE::IRoutedEventManager^ _eventManager;
		};
	}
}
