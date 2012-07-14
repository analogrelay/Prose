#pragma once

#include "CustomRoutedEvent.h"

namespace Prose {
	namespace Events {
		public ref class RoutedEventHandlerInfo {
		public:
			property Windows::Foundation::TypedEventHandler<Platform::Object^, ICustomRoutedEventArgs^>^ Handler { 
				Windows::Foundation::TypedEventHandler<Platform::Object^, ICustomRoutedEventArgs^>^ get() { return _handler; } 
			}
			property bool InvokeHandledEventsToo { bool get() { return _invokeHandledEventsToo; } }

			void InvokeHandler(Platform::Object^ sender, ICustomRoutedEventArgs^ args) {
				if(!args->Handled || InvokeHandledEventsToo) {
					Handler(sender, args);
				}
			}

		internal:
			property UINT64 Id { UINT64 get() { return _id; } };

			RoutedEventHandlerInfo(
				Windows::Foundation::TypedEventHandler<Platform::Object^, ICustomRoutedEventArgs^>^ handler, 
				bool invokeHandledEventsToo, 
				UINT64 id) : _handler(handler), _invokeHandledEventsToo(invokeHandledEventsToo), _id(id) { }

		private:
			Windows::Foundation::TypedEventHandler<Platform::Object^, ICustomRoutedEventArgs^>^ _handler;
			bool _invokeHandledEventsToo;
			UINT64 _id;
		};
	}
}