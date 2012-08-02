#pragma once

#include "Inline.h"
#include "TextPointer.h"

namespace Prose {
	namespace Structure {
		namespace WFC = Windows::Foundation::Collections;
		namespace WUX = Windows::UI::Xaml;

		private ref class Paragraph :
			public StructureNode
		{
		public:
			virtual property WFC::IVector<Inline^>^ Inlines {
				WFC::IVector<Inline^>^ get() { return _inlines; }
			};

			virtual void Accept(StructureVisitor^ visitor) override;
			Paragraph^ Clone(void);

		internal:
			Paragraph(void);

			TextPointer^ OffsetToPointer(UINT32 offset);

		private:
			WFC::IVector<Inline^>^ _inlines;
		};
	}
}