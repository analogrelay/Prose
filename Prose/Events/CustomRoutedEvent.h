#pragma once

namespace Prose {
	namespace Events {
		public interface class ICustomRoutedEventArgs
		{
			property Platform::Object^ OriginalSource;
			property bool Handled;
		};

		public delegate void CustomRoutedEventHandler(Platform::Object^ sender, ICustomRoutedEventArgs^ e);
	}
}