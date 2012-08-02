#pragma once

#include <limits>
#include <list>

namespace Prose {
	namespace WUX = Windows::UI::Xaml;
	namespace WUT = Windows::UI::Text; // WUT? :)

	private ref class TextFormat sealed :
		public Windows::UI::Xaml::DependencyObject
	{
	public:
		TextFormat(void) { }

		TextFormat^ MergeWith(TextFormat^ overridingCopy);
		TextFormat^ Clone(void);
	internal:
		virtual property WUX::Media::FontFamily^ FontFamily;
		virtual property Nullable<double> FontSize;
		virtual property WUX::Media::Brush^ Foreground;
		virtual property WUT::FontStretch FontStretch;
		virtual property Nullable<WUT::FontStyle>FontStyle;
		virtual property Nullable<WUT::FontWeight> FontWeight;
		virtual property Nullable<bool> HasStrikethrough;
		virtual property Nullable<bool> HasUnderline;	

		void ApplyDeviceIndependent(Microsoft::WRL::ComPtr<IDWriteTextLayout> layout, UINT32 start, UINT32 length);
		void ApplyDeviceDependent(Microsoft::WRL::ComPtr<ID2D1RenderTarget> target, Microsoft::WRL::ComPtr<IDWriteTextLayout> layout, UINT32 offset, UINT32 length);

		static TextFormat^ MergeSequence(std::list<TextFormat^>& list);
	private:
		Microsoft::WRL::ComPtr<ID2D1Brush> ConvertBrush(Microsoft::WRL::ComPtr<ID2D1RenderTarget> target, Windows::UI::Xaml::Media::Brush^ xamlBrush);
	};
}