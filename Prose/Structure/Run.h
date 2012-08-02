#pragma once

#include "Inline.h"

namespace Prose {
	namespace Structure {
		namespace WUX = Windows::UI::Xaml;

		private ref class Run :
			public Inline
		{
		public:
			virtual property Platform::String^ Text {
				Platform::String^ get() { return _text; }
				void set(Platform::String^ value) { _text = value; }
			};

			virtual property UINT32 Length {
				UINT32 get() override { return _text->Length(); }
			}

			virtual void Accept(StructureVisitor^ visitor) override;
			virtual InlinePair^ Split(UINT32 localOffset) override;

		internal:
			Run(void);
			Run(Platform::String^);

		private:
			Platform::String^ _text;
		};
	}
}