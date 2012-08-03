#pragma once

#include "Inline.h"

namespace Prose {
	namespace Structure {
		namespace WFC = Windows::Foundation::Collections;
		namespace WUX = Windows::UI::Xaml;

		ref class StructureVisitor;

		private ref class Span abstract :
			public Inline
		{
		public:
			virtual property UINT32 Length { UINT32 get() override; }
			virtual InlinePair^ Split(UINT32 localOffset) override;

			virtual property WFC::IVector<Inline^>^ Inlines {
				WFC::IVector<Inline^>^ get() { 
					return _inlines;
				}
			};

			virtual void Accept(StructureVisitor^ visitor) override;

		public protected:
			virtual Span^ Clone() abstract;

		private protected:
			Span(void);

		private:
			WFC::IVector<Inline^>^ _inlines;
		};
	}
}