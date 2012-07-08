#pragma once

#include "..\Events\PointerTextEvents.h"

namespace Prose {
	namespace Structure {
		ref class DocumentVisitor;

		public ref class DocumentNode : 
			public Windows::UI::Xaml::DependencyObject
		{
		public:
			virtual event Prose::Events::PointerTextEventHandler^ PointerEntered;
			virtual event Windows::UI::Xaml::Data::PropertyChangedEventHandler^ PropertyChanged;

			virtual void Accept(DocumentVisitor^ visitor) { dbgf(L"Accept was called but is not implemented for this sub-class"); };

			/// <summary>Not intended to be called by user-code</summary>
			virtual void FirePointerEntered(Prose::Events::PointerTextEventArgs^ args);

		protected:
			virtual void OnPropertyChanged(Platform::String^ propertyName) {
				PropertyChanged(this, ref new Windows::UI::Xaml::Data::PropertyChangedEventArgs(propertyName));
			}
		};
	}
}
