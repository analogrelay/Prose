#pragma once
class DWriteFactory {
public:
	static IDWriteFactory* GetFactory() {
		return _theFactory.GetFactoryCore();
	};

private:
	static DWriteFactory _theFactory;

	DWriteFactory(void);

	IDWriteFactory* GetFactoryCore();

	IDWriteFactory* _factory;
};

