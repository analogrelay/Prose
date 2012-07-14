#pragma once

#include "DocumentNode.h"
#include "InlinePair.h"
#include "..\TextFormat.h"

#include <limits>

namespace Prose {
	namespace Structure {
		ref class DocumentVisitor;

		public ref class Inline :
			public DocumentNode
		{
			DEPENDENCY_PROPERTY(Windows::UI::Xaml::Media::FontFamily^, FontFamily);
			DEPENDENCY_PROPERTY(double, FontSize);
			DEPENDENCY_PROPERTY(Windows::UI::Xaml::Media::Brush^, Foreground);
			DEPENDENCY_PROPERTY(Windows::UI::Text::FontStretch, FontStretch);
			DEPENDENCY_PROPERTY(Windows::UI::Text::FontStyle, FontStyle);
			DEPENDENCY_PROPERTY(Windows::UI::Text::FontWeight, FontWeight);
			DEPENDENCY_PROPERTY(bool, HasStrikethrough);
			DEPENDENCY_PROPERTY(bool, HasUnderline);
			
		public:
			virtual property UINT32 Length { UINT32 get() { throw ref new Platform::NotImplementedException(L"Inline.Length must be implemented on subclasses of Inline"); } }
			virtual InlinePair^ Split(UINT32 localOffset) { throw ref new Platform::NotImplementedException(L"Inline.Split must be implemented on subclasses of Inline"); };

			/// <summary>Creates a TextFormat representing this node</summary>
			TextFormat^ CreateFormat(void);

			virtual void Accept(DocumentVisitor^ visitor) override;

		public protected:
			void CopyStyleTo(Inline^ other);

		private:
			void InvalidateFormat();

			static void FormatPropertyChanged(
				Windows::UI::Xaml::DependencyObject^ sender, 
				Windows::UI::Xaml::DependencyPropertyChangedEventArgs^ args);
		};
	}
}