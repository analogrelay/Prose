#pragma once

#include "InlineNode.h"

namespace Prose {
	namespace Structure {
		namespace WFC = Windows::Foundation::Collections;
		namespace WUX = Windows::UI::Xaml;

		ref class StructureVisitor;

		private ref class SpanNode :
			public InlineNode
		{
		public:
			virtual property UINT32 Length { UINT32 get() override; }
			virtual InlinePair^ Split(UINT32 localOffset, TextFormat^ effectiveFormat) override;

			virtual property WFC::IVector<InlineNode^>^ Inlines {
				WFC::IVector<InlineNode^>^ get() { 
					return _inlines;
				}
			};

			virtual void Accept(StructureVisitor^ visitor) override;

		internal:
			SpanNode(void);

		private:
			WFC::IVector<InlineNode^>^ _inlines;
		};
	}
}