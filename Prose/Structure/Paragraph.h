#pragma once
#include "DocumentNode.h"
#include "Run.h"

namespace Prose {
	namespace Structure {
		[Windows::UI::Xaml::Markup::ContentProperty(Name = "Runs")]
		public ref class Paragraph sealed :
			public DocumentNode
		{
		public:
			Paragraph(void);

			property Windows::Foundation::Collections::IVector<Run^>^ Runs {
				Windows::Foundation::Collections::IVector<Run^>^ get() { return _runs; }
			};

			virtual void Accept(DocumentVisitor^ visitor) override;

			Paragraph^ Clone(void);
		private:
			Windows::Foundation::Collections::IVector<Run^>^ _runs;
		};
	}
}