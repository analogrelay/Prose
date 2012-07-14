#pragma once

#include "Inline.h"

namespace Prose {
	namespace Structure {

		public interface class IRun :
			public IInline {

			property Platform::String^ Text;
		};

		[Windows::UI::Xaml::Markup::ContentProperty(Name = "Text")]
		public ref class Run sealed :
			public Inline,
			public IRun
		{
		public:
			Run(void);
			Run(Platform::String^);

			virtual property Platform::String^ Text {
				Platform::String^ get() { return _text; }
				void set(Platform::String^ value) { _text = value; }
			};

			virtual property UINT32 Length {
				UINT32 get() override { return _text->Length(); }
			}

			virtual void Accept(DocumentVisitor^ visitor) override;
			virtual IInlinePair^ Split(UINT32 localOffset) override;

		private:
			Platform::String^ _text;
		};
	}
}