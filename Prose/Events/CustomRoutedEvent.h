#pragma once

namespace Prose {
	namespace Events {
		public interface class ICustomRoutedEventArgs
		{
			property Platform::Object^ OriginalSource { Platform::Object^ get(); }
			property bool Handled;
		};

		private ref class CustomRoutedEventArgs :
			public ICustomRoutedEventArgs {
		public:
			virtual property Platform::Object^ OriginalSource {
				Platform::Object^ get() { return _originalSource; }
			}

			virtual property bool Handled {
				bool get() { return _handled; }
				void set(bool value) { _handled = value; }
			}

		internal:
			CustomRoutedEventArgs(Platform::Object^ originalSource) : _originalSource(originalSource), _handled(false) {}

		private:
			Platform::Object^ _originalSource;
			bool _handled;
		};

		public delegate void CustomRoutedEventHandler(Platform::Object^ sender, ICustomRoutedEventArgs^ e);
	}
}