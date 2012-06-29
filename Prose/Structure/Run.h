#pragma once
#include "DocumentNode.h"

namespace Prose {
	namespace Structure {
		[Windows::UI::Xaml::Markup::ContentProperty(Name = "Text")]
		public ref class Run sealed :
			public DocumentNode
		{
		public:
			Run(void);
			Run(Platform::String^);

			property Platform::String^ Text {
				Platform::String^ get() { return _text; }
				void set(Platform::String^ value) { _text = value; }
			};

			virtual void Accept(DocumentVisitor^ visitor) override;

		private:
			Platform::String^ _text;
		};
	}
}