#pragma once
namespace Prose {
	namespace Fonts {
		using namespace Platform;

		public ref class FontFamily sealed
		{
		public:
			property Array<String^>^ FamilyNames {
				Array<String^>^ get() { return GetFamilyNames(); }
			};

		internal:
			FontFamily(IDWriteFontFamily*);

		private:
			Array<String^>^ _familyNames;
			IDWriteFontFamily* _family;

			Array<String^>^ GetFamilyNames();
		};
	}
}