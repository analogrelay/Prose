#pragma once

class DX {
public:
	static Microsoft::WRL::ComPtr<ID2D1Factory1> GetD2DFactory() {
		return _theFactory.GetD2DFactoryCore();
	}

	static Microsoft::WRL::ComPtr<IDWriteFactory> GetDWFactory() {
		return _theFactory.GetDWFactoryCore();
	};

	static Microsoft::WRL::ComPtr<IDWriteFontCollection> GetSystemFonts() {
		return _theFactory.GetSystemFontsCore();
	};

	static void ToNativeRect(Windows::Foundation::Rect rect, RECT* pRect);
	static D2D1_COLOR_F ToDXColor(Windows::UI::Color winColor);
	static D2D1_POINT_2F ToDXPoint(Windows::Foundation::Point winPoint);
	static D2D1_BRUSH_PROPERTIES ToDXBrushProperties(Windows::UI::Xaml::Media::Brush^ winBrush);
private:
	static DX _theFactory;

	DX(void);

	Microsoft::WRL::ComPtr<ID2D1Factory1> GetD2DFactoryCore();
	Microsoft::WRL::ComPtr<IDWriteFactory> GetDWFactoryCore();
	Microsoft::WRL::ComPtr<IDWriteFontCollection> GetSystemFontsCore();

	Microsoft::WRL::ComPtr<IDWriteFontCollection> _systemFonts;
	Microsoft::WRL::ComPtr<IDWriteFactory> _dwFactory;
	Microsoft::WRL::ComPtr<ID2D1Factory1> _d2dFactory;
};

