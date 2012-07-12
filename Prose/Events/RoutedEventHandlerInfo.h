#pragma once

#include "CustomRoutedEvent.h"

namespace Prose {
	namespace Events {
		public ref class RoutedEventHandlerInfo {
		public:
			property CustomRoutedEventHandler^ Handler { CustomRoutedEventHandler^ get() { return _handler; } }
			property bool InvokeHandledEventsToo { bool get() { return _invokeHandledEventsToo; } }

			void InvokeHandler(Platform::Object^ sender, ICustomRoutedEventArgs^ args) {
				if(!args->Handled || InvokeHandledEventsToo) {
					Handler(sender, args);
				}
			}

		internal:
			property UINT64 Id { UINT64 get() { return _id; } };

			RoutedEventHandlerInfo(CustomRoutedEventHandler^ handler, bool invokeHandledEventsToo, UINT64 id) : _handler(handler), _invokeHandledEventsToo(invokeHandledEventsToo), _id(id) { }

		private:
			CustomRoutedEventHandler^ _handler;
			bool _invokeHandledEventsToo;
			UINT64 _id;
		};
	}
}