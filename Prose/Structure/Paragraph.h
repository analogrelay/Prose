#pragma once
#include "DocumentNode.h"
#include "Inline.h"
#include "TextPointer.h"
#include "Run.h"
#include "DocumentVisitor.h"

namespace Prose {
	namespace Structure {
		ref class DocumentVisitor;

		[Windows::UI::Xaml::Markup::ContentProperty(Name = "Inlines")]
		public ref class Paragraph sealed :
			public DocumentNode
		{
		public:
			Paragraph(void);

			property Windows::Foundation::Collections::IVector<Inline^>^ Inlines {
				Windows::Foundation::Collections::IVector<Inline^>^ get() { return _inlines; }
			};

			virtual void Accept(DocumentVisitor^ visitor) override;

			Paragraph^ Clone(void);

			TextPointer^ OffsetToPointer(UINT32 offset);
		private:
			Windows::Foundation::Collections::IVector<Inline^>^ _inlines;
		};
	}
}