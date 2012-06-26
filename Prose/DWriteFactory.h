#pragma once

using namespace Microsoft::WRL;

class DWriteFactory {
public:
	static ComPtr<IDWriteFactory> GetFactory() {
		return _theFactory.GetFactoryCore();
	};

	static ComPtr<IDWriteFontCollection> GetSystemFonts() {
		return _theFactory.GetSystemFontsCore();
	};

private:
	static DWriteFactory _theFactory;

	DWriteFactory(void);

	ComPtr<IDWriteFactory> GetFactoryCore();
	ComPtr<IDWriteFontCollection> GetSystemFontsCore();

	ComPtr<IDWriteFontCollection> _systemFonts;
	ComPtr<IDWriteFactory> _factory;
};

