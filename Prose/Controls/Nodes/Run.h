#pragma once

#include "DocumentNode.h"

namespace Prose {
	namespace Controls {
		namespace WFM = Windows::Foundation::Metadata;
		namespace WUX = Windows::UI::Xaml;
		namespace WFC = Windows::Foundation::Collections;

		[WFM::WebHostHidden]
		[WUX::Markup::ContentProperty(Name = "Text")]
		public ref class Run sealed :
			public Inline
		{
			DEPENDENCY_PROPERTY(Platform::String^, Text);

		public:
			Run(void);

		internal:
			virtual Prose::Structure::InlineNode^ ConstructStructureNode(void) override;
		};
	}
}