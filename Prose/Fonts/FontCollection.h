#pragma once
#include <dwrite.h>
#include "FontFamily.h"

namespace Prose {
	namespace Fonts {
		using namespace Windows::Foundation::Collections;
		public ref class FontCollection sealed :
			public IIterable<FontFamily^>
		{
		public:
			property FontFamily^ default[Platform::String^] {
				FontFamily^ get(Platform::String^ name) { return GetFontFamily(name); }
			}

			property UINT32 Count {
				UINT32 get() { return GetFontFamilyCount(); }
			}

			static property FontCollection^ SystemFonts {
				FontCollection^ get() { return GetSystemFonts(); }
			}

			virtual IIterator<FontFamily^>^ First();

		private:
			FontCollection(IDWriteFontCollection*);

			static FontCollection^ GetSystemFonts();

			UINT32 GetFontFamilyCount();
			FontFamily^ GetFontFamily(Platform::String^ name);
			FontFamily^ GetFontFamily(UINT32 index);

			IDWriteFontCollection* _collection;

			ref class FontFamilyIterator sealed :
				public IIterator<FontFamily^>
			{
			public:
				property FontFamily^ Current {
					virtual FontFamily^ get() { return _current; }
				};

				property bool HasCurrent {
					virtual bool get() { return _hasCurrent; }
				};

				virtual UINT32 GetMany(WriteOnlyArray<FontFamily^>^ items);
				virtual bool MoveNext();
			
			internal:
				FontFamilyIterator(FontCollection^ collection);

			private:
				FontCollection^ _collection;
				UINT32 _count;
				UINT32 _position;
				

				FontFamily^ _current;
				bool _hasCurrent;
			};
		};
	}
}