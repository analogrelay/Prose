#pragma once

#include "BaseNodes.h"

namespace Prose {
	namespace Controls {
		namespace WFM = Windows::Foundation::Metadata;
		namespace WUX = Windows::UI::Xaml;
		namespace WFC = Windows::Foundation::Collections;

		[WFM::WebHostHidden]
		[WUX::Markup::ContentProperty(Name = "Children")]
		public ref class SpanBase :
			public Inline
		{
		public:
			property WFC::IVector<Inline^>^ Children {
				WFC::IVector<Inline^>^ get() { return _children; }
			}

		internal:
			SpanBase(void);

			virtual Prose::Structure::InlineNode^ ConstructStructureNode(void) override;

		private:
			WFC::IVector<Inline^>^ _children;
		};

		[WFM::WebHostHidden]
		[WUX::Markup::ContentProperty(Name = "Children")]
		public ref class Span sealed :
			public SpanBase
		{
		public:
			Span(void) : SpanBase() { }
		};

		[WFM::WebHostHidden]
		[WUX::Markup::ContentProperty(Name = "Children")]
		public ref class Italic sealed :
			public SpanBase
		{
		public:
			Italic(void);
		};

		[WFM::WebHostHidden]
		[WUX::Markup::ContentProperty(Name = "Children")]
		public ref class Bold sealed :
			public SpanBase
		{
		public:
			Bold(void);
		};

		[WFM::WebHostHidden]
		[WUX::Markup::ContentProperty(Name = "Children")]
		public ref class Underline sealed :
			public SpanBase
		{
		public:
			Underline(void);
		};
	}
}