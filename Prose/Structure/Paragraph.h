#pragma once

#include "Inline.h"

namespace Prose {
	namespace Structure {
		namespace WFC = Windows::Foundation::Collections;
		namespace WUX = Windows::UI::Xaml;

		public interface class IParagraph :
			public IDocumentNode {
			
			property WFC::IVector<IInline^>^ Inlines {
				WFC::IVector<IInline^>^ get();
			}
		};

		[WUX::Markup::ContentProperty(Name = "Inlines")]
		private ref class Paragraph :
			public DocumentNode,
			public IParagraph
		{
		public:
			virtual property WFC::IVector<IInline^>^ Inlines {
				WFC::IVector<IInline^>^ get() { return _inlines; }
			};

			TextPointer^ OffsetToPointer(UINT32 offset);
			virtual void Accept(IDocumentVisitor^ visitor) override;
		internal:
			Paragraph(void);

		private:
			WFC::IVector<IInline^>^ _inlines;
		};
	}
}