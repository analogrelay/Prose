#pragma once

#include "DocumentNode.h"

namespace Prose {
	ref class TextFormat;

	namespace Structure {
		namespace WUX = Windows::UI::Xaml;
		namespace WUT = Windows::UI::Text; // WUT? :)

		interface class IInlinePair;
		interface class IDocumentVisitor;
		
		public interface class IInline {
			property WUX::Media::FontFamily^ FontFamily;
			property double FontSize;
			property WUX::Media::Brush^ Foreground;
			property WUT::FontStretch FontStretch;
			property WUT::FontStyle FontStyle;
			property WUT::FontWeight FontWeight;
			property bool HasStrikethrough;
			property bool HasUnderline;

			property UINT32 Length { UINT32 get(); }

			IInlinePair^ Split(UINT32 at);
		};

		private ref class Inline abstract :
			public DocumentNode,
			public IInline
		{
		public:
			virtual property WUX::Media::FontFamily^ FontFamily;
			virtual property double FontSize;
			virtual property WUX::Media::Brush^ Foreground;
			virtual property WUT::FontStretch FontStretch;
			virtual property WUT::FontStyle FontStyle;
			virtual property WUT::FontWeight FontWeight;
			virtual property bool HasStrikethrough;
			virtual property bool HasUnderline;
			
			virtual property UINT32 Length { UINT32 get() FAUX_ABSTRACT }
			virtual IInlinePair^ Split(UINT32 localOffset) FAUX_ABSTRACT;
			
			virtual TextFormat^ CreateFormat(void);
			virtual void CopyStyleTo(IInline^ other);
			virtual void Accept(IDocumentVisitor^ visitor) override;

		private:
			Inline(void) { }

			void InvalidateFormat();

			static void FormatPropertyChanged(
				WUX::DependencyObject^ sender, 
				WUX::DependencyPropertyChangedEventArgs^ args);
		};
	}
}