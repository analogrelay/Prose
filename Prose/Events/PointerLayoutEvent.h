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
		namespace PL = Prose::Layout;
		namespace WUX = Windows::UI::Xaml;

		public interface class IPointerLayoutEventArgs :
			public ICustomRoutedEventArgs {

			property PL::LayoutPointer^ LayoutPointer {
				PL::LayoutPointer^ get();
			}

			property WUX::Input::PointerRoutedEventArgs^ PointerInfo {
				WUX::Input::PointerRoutedEventArgs^ get();
			}
		};

		public delegate void PointerLayoutEventHandler(Platform::Object^ sender, IPointerLayoutEventArgs^ args);

		private ref class PointerLayoutEventArgs sealed :
			public CustomRoutedEventArgs,
			public IPointerLayoutEventArgs
		{
		public:
			virtual property Platform::Object^ OriginalSource { Platform::Object^ get() override { return CustomRoutedEventArgs::OriginalSource; } };
			virtual property bool Handled { 
				bool get() override { return CustomRoutedEventArgs::Handled; } 
				void set(bool value) override { CustomRoutedEventArgs::Handled = value; }
			};

			virtual property PL::LayoutPointer^ LayoutPointer {
				PL::LayoutPointer^ get() { return _layoutPointer; }
			}

			virtual property WUX::Input::PointerRoutedEventArgs^ PointerInfo {
				WUX::Input::PointerRoutedEventArgs^ get() { return _pointerInfo; }
			}
			
			PointerLayoutEventArgs(Platform::Object^ originalSource, PL::LayoutPointer^ layoutPointer, WUX::Input::PointerRoutedEventArgs^ pointerInfo) :
				CustomRoutedEventArgs(originalSource), _layoutPointer(layoutPointer), _pointerInfo(pointerInfo) { }
		private:
			PL::LayoutPointer^ _layoutPointer;
			WUX::Input::PointerRoutedEventArgs^ _pointerInfo;
		};
	}
}
