#pragma once

#include "RoutedEvent.h"

namespace Prose {
	namespace Events {
		public enum class RoutingStrategy {
		};

		public ref class EventManager sealed
		{
		public:
			static RoutedEvent^ RegisterRoutedEvent(
				Platform::String^ name,
				RoutingStrategy routingStrategy,
				Platform::Type^ handlerType,
				Platform::Type^ ownerType);

		private:
			EventManager(void) {};
		};
	}
}