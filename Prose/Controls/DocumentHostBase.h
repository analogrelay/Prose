#pragma once

namespace Prose {
	namespace Controls {
		ref class OverflowDocumentHost;

		public ref class DocumentHostBase :
			public Windows::UI::Xaml::Controls::Panel
		{
		public:
			static property Windows::UI::Xaml::DependencyProperty^ OverflowTargetProperty {
				Windows::UI::Xaml::DependencyProperty^ get() { return _OverflowTargetProperty; }
			};

			virtual property OverflowDocumentHost^ OverflowTarget {
				OverflowDocumentHost^ get() { return (OverflowDocumentHost^)GetValue(OverflowTargetProperty); }
				void set(OverflowDocumentHost^ value) { SetValue(OverflowTargetProperty, value); }
			};

			property bool HasOverflowContent {
				bool get() { return _hasOverflowContent; }
				void set(bool value) { _hasOverflowContent = value; }
			};

		private:
			bool _hasOverflowContent;
			static Windows::UI::Xaml::DependencyProperty^ _OverflowTargetProperty;

			void SendOverflow(void);
			static void TargetChanged(Windows::UI::Xaml::DependencyObject^, Windows::UI::Xaml::DependencyPropertyChangedEventArgs^);
		};
	}
}