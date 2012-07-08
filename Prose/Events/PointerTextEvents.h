#pragma once

namespace Prose {
	namespace Structure {
		ref class TextPointer;
	}
	namespace Layout {
		ref class LayoutPointer;
	}
	namespace Events {
		public ref class PointerTextEventArgs sealed
		{
		public:
			property Prose::Structure::TextPointer^ TextPointer {
				Prose::Structure::TextPointer^ get() { return _textPointer; }
			}

			property Windows::UI::Xaml::Input::PointerRoutedEventArgs^ PointerInfo {
				Windows::UI::Xaml::Input::PointerRoutedEventArgs^ get() { return _pointerInfo; }
			}
			
			PointerTextEventArgs(Prose::Structure::TextPointer^ textPointer, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ pointerInfo) :
				_textPointer(textPointer), _pointerInfo(pointerInfo) { }
		private:
			Prose::Structure::TextPointer^ _textPointer;
			Windows::UI::Xaml::Input::PointerRoutedEventArgs^ _pointerInfo;
		};

		public ref class PointerLayoutEventArgs sealed
		{
		public:
			property Prose::Layout::LayoutPointer^ LayoutPointer {
				Prose::Layout::LayoutPointer^ get() { return _layoutPointer; }
			}

			property Windows::UI::Xaml::Input::PointerRoutedEventArgs^ PointerInfo {
				Windows::UI::Xaml::Input::PointerRoutedEventArgs^ get() { return _pointerInfo; }
			}
			
			PointerLayoutEventArgs(Prose::Layout::LayoutPointer^ layoutPointer, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ pointerInfo) :
				_layoutPointer(layoutPointer), _pointerInfo(pointerInfo) { }
		private:
			Prose::Layout::LayoutPointer^ _layoutPointer;
			Windows::UI::Xaml::Input::PointerRoutedEventArgs^ _pointerInfo;
		};

		public delegate void PointerLayoutEventHandler(Platform::Object^ sender, PointerLayoutEventArgs^ args);
		public delegate void PointerTextEventHandler(Platform::Object^ sender, PointerTextEventArgs^ args);
	}
}
