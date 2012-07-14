#pragma once

#include "DocumentNode.h"

namespace Prose {
	ref class TextFormat;

	namespace Structure {
		interface class IInlinePair;
		interface class IDocumentVisitor;
		
		public interface class IInline :
			public IDocumentNode {

			property Windows::UI::Xaml::Media::FontFamily^ FontFamily;
			property double FontSize;
			property Windows::UI::Xaml::Media::Brush^ Foreground;
			property Windows::UI::Text::FontStretch FontStretch;
			property Windows::UI::Text::FontStyle FontStyle;
			property Windows::UI::Text::FontWeight FontWeight;
			property bool HasStrikethrough;
			property bool HasUnderline;

			property UINT32 Length { UINT32 get(); }

			IInlinePair^ Split(UINT32 at);
		};

		public ref class Inline :
			public DocumentNode,
			public IInline
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
			virtual property UINT32 Length { UINT32 get() FAUX_ABSTRACT }
			virtual IInlinePair^ Split(UINT32 localOffset) FAUX_ABSTRACT;
			
			virtual TextFormat^ CreateFormat(void);
			virtual void CopyStyleTo(IInline^ other);
			virtual void Accept(IDocumentVisitor^ visitor) override;

		private:
			Inline(void) { }

			void InvalidateFormat();

			static void FormatPropertyChanged(
				Windows::UI::Xaml::DependencyObject^ sender, 
				Windows::UI::Xaml::DependencyPropertyChangedEventArgs^ args);
		};
	}
}