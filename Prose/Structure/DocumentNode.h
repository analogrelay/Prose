#pragma once

namespace Prose {
	namespace Structure {
		ref class DocumentVisitor;

		public ref class DocumentNode abstract
			: public Windows::UI::Xaml::Data::INotifyPropertyChanged
		{
		public:
			virtual void Accept(DocumentVisitor^ visitor) = 0;
			virtual event Windows::UI::Xaml::Data::PropertyChangedEventHandler^ PropertyChanged;
		
		protected:
			virtual void OnPropertyChanged(Platform::String^ propertyName) {
				PropertyChanged(this, ref new Windows::UI::Xaml::Data::PropertyChangedEventArgs(propertyName));
			}
		};
	}
}