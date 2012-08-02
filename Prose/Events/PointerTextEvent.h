#pragma once

#include "CustomRoutedEvent.h"

namespace Prose {
	namespace Structure {
		ref class TextPointer;
	}
	
	namespace Layout {
		ref class LayoutPointer;
	}

	namespace Events {
		namespace PS = Prose::Structure;
		namespace WUX = Windows::UI::Xaml;

		private ref class PointerTextEventArgs sealed :
			public CustomRoutedEventArgs
		{
		public:
			virtual property Platform::Object^ OriginalSource { Platform::Object^ get() override { return CustomRoutedEventArgs::OriginalSource; } };
			virtual property bool Handled { 
				bool get() override { return CustomRoutedEventArgs::Handled; } 
				void set(bool value) override { CustomRoutedEventArgs::Handled = value; }
			};

			virtual property PS::TextPointer^ TextPointer {
				PS::TextPointer^ get() { return _textPointer; }
			}

			virtual property WUX::Input::PointerRoutedEventArgs^ PointerInfo {
				WUX::Input::PointerRoutedEventArgs^ get() { return _pointerInfo; }
			}

			PointerTextEventArgs(Platform::Object^ originalSource, PS::TextPointer^ textPointer, WUX::Input::PointerRoutedEventArgs^ pointerInfo) :
				CustomRoutedEventArgs(originalSource), _textPointer(textPointer), _pointerInfo(pointerInfo) { }
		private:
			PS::TextPointer^ _textPointer;
			WUX::Input::PointerRoutedEventArgs^ _pointerInfo;
		};
	}
}