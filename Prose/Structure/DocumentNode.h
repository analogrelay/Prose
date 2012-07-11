#pragma once

namespace Prose {
	namespace Structure {
		ref class DocumentVisitor;

		public ref class DocumentNode : 
			public Windows::UI::Xaml::DependencyObject
		{
		public:
			virtual void Accept(DocumentVisitor^ visitor) { dbgf(L"Accept was called but is not implemented for this sub-class"); };
			virtual event Windows::UI::Xaml::Data::PropertyChangedEventHandler^ PropertyChanged;

		protected:
			virtual void OnPropertyChanged(Platform::String^ propertyName) {
				PropertyChanged(this, ref new Windows::UI::Xaml::Data::PropertyChangedEventArgs(propertyName));
			}
		};
	}
}