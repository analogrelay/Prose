#pragma once

#include "EventManager.h"

namespace Prose {
	namespace Events {
		public ref class RoutedEvent
		{
		public:
			property Platform::String^ Name { Platform::String^ get() { return _name; } }
			property Events::RoutingStrategy RoutingStrategy { Events::RoutingStrategy get() { return _routingStrategy; } }
			property Platform::Type^ HandlerType { Platform::Type^ get() { return _handlerType; } }
			property Platform::Type^ OwnerType { Platform::Type^ get() { return _ownerType; } }

		internal:
			RoutedEvent(Platform::String^ name, Events::RoutingStrategy routingStrategy, Platform::Type^ handlerType, Platform::Type^ ownerType) :
				_name(name), _routingStrategy(routingStrategy), _handlerType(handlerType), _ownerType(ownerType), _id(EventManager::GetNextEventId()) {}

		private:
			Platform::String^ _name;
			Events::RoutingStrategy _routingStrategy;
			Platform::Type^ _handlerType;
			Platform::Type^ _ownerType;
			UINT64 _id;
		};
	}
}

namespace std {
	template<>
	struct less<Prose::Events::RoutedEvent^> {
		bool operator()(Prose::Events::RoutedEvent^ left, Prose::Events::RoutedEvent^ right) {
			return left->Name < right->Name;
		}
	};
}