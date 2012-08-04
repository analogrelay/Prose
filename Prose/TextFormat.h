#pragma once

#include <limits>
#include <deque>

namespace Prose {
	namespace WUX = Windows::UI::Xaml;
	namespace WUT = Windows::UI::Text; // WUT? :)

	// Internal representation of a TextStyle
	private ref class TextFormat sealed
	{
	public:
		TextFormat(void) { }

		TextFormat^ MergeWith(TextFormat^ overridingCopy);
		TextFormat^ Clone(void);
	internal:
		property bool AnythingSet {
			bool get();
		}

		virtual property WUX::Media::FontFamily^ FontFamily {
			WUX::Media::FontFamily^ get() { return _fontFamily; }
			void set(WUX::Media::FontFamily^ value) { _fontFamily = value; }
		}

		virtual property Nullable<double> FontSize {
			Nullable<double> get() { return _fontSize; }
			void set(Nullable<double> value) { _fontSize = value; }
		}

		virtual property WUX::Media::Brush^ Foreground {
			WUX::Media::Brush^ get() { return _foreground; }
			void set(WUX::Media::Brush^ value) { _foreground = value; }
		}

		virtual property WUT::FontStretch FontStretch {
			WUT::FontStretch get() { return _fontStretch; }
			void set(WUT::FontStretch value) { _fontStretch = value; }
		}

		virtual property Nullable<WUT::FontStyle> FontStyle {
			Nullable<WUT::FontStyle> get() { return _fontStyle; }
			void set(Nullable<WUT::FontStyle> value) { _fontStyle = value; }
		}

		virtual property Nullable<WUT::FontWeight> FontWeight {
			Nullable<WUT::FontWeight> get() { return _fontWeight; }
			void set(Nullable<WUT::FontWeight> value) { _fontWeight = value; }
		}

		virtual property Nullable<bool> HasStrikethrough {
			Nullable<bool> get() { return _hasStrikethrough; }
			void set(Nullable<bool> value) { _hasStrikethrough = value; }
		}

		virtual property Nullable<bool> HasUnderline {
			Nullable<bool> get() { return _hasUnderline; }
			void set(Nullable<bool> value) { _hasUnderline = value; }
		}

		void ApplyDeviceIndependent(Microsoft::WRL::ComPtr<IDWriteTextLayout> layout, UINT32 start, UINT32 length);
		void ApplyDeviceDependent(Microsoft::WRL::ComPtr<ID2D1RenderTarget> target, Microsoft::WRL::ComPtr<IDWriteTextLayout> layout, UINT32 offset, UINT32 length);

		static TextFormat^ MergeSequence(std::deque<TextFormat^> const& list);
	private:
		Microsoft::WRL::ComPtr<ID2D1Brush> ConvertBrush(Microsoft::WRL::ComPtr<ID2D1RenderTarget> target, Windows::UI::Xaml::Media::Brush^ xamlBrush);

		WUX::Media::FontFamily^ _fontFamily;
		Nullable<double> _fontSize;
		WUX::Media::Brush^ _foreground;
		WUT::FontStretch _fontStretch;
		Nullable<WUT::FontStyle> _fontStyle;
		Nullable<WUT::FontWeight> _fontWeight;
		Nullable<bool> _hasStrikethrough;
		Nullable<bool> _hasUnderline;	
	};
}