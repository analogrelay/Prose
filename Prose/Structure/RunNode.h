#pragma once

#include "InlineNode.h"

namespace Prose {
	namespace Structure {
		namespace WUX = Windows::UI::Xaml;

		private ref class RunNode :
			public InlineNode
		{
		public:
			virtual property Platform::String^ Text {
				Platform::String^ get() { return _text; }
				void set(Platform::String^ value) { 
					_text = value; 
#ifdef _DEBUG
					_ctext = _text->Data();
#endif
				}
			};

			virtual property UINT32 Length {
				UINT32 get() override { return _text->Length(); }
			}

			virtual void Accept(StructureVisitor^ visitor) override;
			virtual InlinePair^ Split(UINT32 localOffset, TextFormat^ effectiveFormat) override;

		internal:
			RunNode(void);
			RunNode(Platform::String^);

		private:
			Platform::String^ _text;
#ifdef _DEBUG
			const wchar_t* _ctext;
#endif
		};
	}
}