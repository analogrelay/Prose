#pragma once

#include "Inline.h"

namespace Prose {
	namespace Structure {
		public interface class IParagraph :
			public IDocumentNode {
			
			property Windows::Foundation::Collections::IVector<IInline^>^ Inlines {
				Windows::Foundation::Collections::IVector<IInline^>^ get();
			}
		};

		[Windows::UI::Xaml::Markup::ContentProperty(Name = "Inlines")]
		public ref class Paragraph sealed :
			public DocumentNode,
			public IParagraph
		{
		public:
			Paragraph(void);

			virtual property Windows::Foundation::Collections::IVector<IInline^>^ Inlines {
				Windows::Foundation::Collections::IVector<IInline^>^ get() { return _inlines; }
			};

			TextPointer^ OffsetToPointer(UINT32 offset);
			virtual void Accept(DocumentVisitor^ visitor) override;
		private:
			Windows::Foundation::Collections::IVector<IInline^>^ _inlines;
		};
	}
}