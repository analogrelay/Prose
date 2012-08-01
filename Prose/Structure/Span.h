#pragma once

#include "Inline.h"

namespace Prose {
	namespace Structure {
		namespace WFC = Windows::Foundation::Collections;
		namespace WUX = Windows::UI::Xaml;

		ref class DocumentVisitor;

		public interface class ISpan {
			property WFC::IVector<IInline^>^ Inlines {
				WFC::IVector<IInline^>^ get();
			}
		}

		[WUX::Markup::ContentProperty(Name = "Inlines")]
		private ref class SpanBase abstract :
			public Inline,
			public ISpan
		{
		public:
			virtual property UINT32 Length { UINT32 get() override; }
			virtual IInlinePair^ Split(UINT32 localOffset) override;

			virtual property WFC::IVector<IInline^>^ Inlines {
				WFC::IVector<IInline^>^ get() { 
					return _inlines;
				}
			};

			virtual void Accept(DocumentVisitor^ visitor) override;

		public protected:
			virtual SpanBase^ Clone() abstract;

		private protected:
			SpanBase(void);

		private:
			WFC::IVector<IInline^>^ _inlines;
		};

		private ref class Span sealed : public SpanBase {
		public:
			Span(void) : SpanBase() {}

			virtual void Accept(DocumentVisitor^ visitor) override;

		public protected:
			virtual SpanBase^ Clone() override { return ref new Span(); }
		};

		private ref class Italic sealed : public SpanBase {
		public:
			Italic(void) : SpanBase() {
				FontStyle = Windows::UI::Text::FontStyle::Italic;
			}

			virtual void Accept(DocumentVisitor^ visitor) override;

		public protected:
			virtual SpanBase^ Clone() override { return ref new Italic(); }
		};

		private ref class Bold sealed : public SpanBase {
		public:
			Bold(void) : SpanBase() {
				FontWeight = Windows::UI::Text::FontWeights::Bold;
			}

			virtual void Accept(DocumentVisitor^ visitor) override;

		public protected:
			virtual SpanBase^ Clone() override { return ref new Bold(); }
		};

		private ref class Underline sealed : public SpanBase {
		public:
			Underline(void) : SpanBase() {
				this->HasUnderline = true;
			}

			virtual void Accept(DocumentVisitor^ visitor) override;

		public protected:
			virtual SpanBase^ Clone() override { return ref new Underline(); }
		};

		private ref class Strikethrough sealed : public SpanBase {
		public:
			Strikethrough(void) : SpanBase() {
				this->HasStrikethrough = true;
			}

			virtual void Accept(DocumentVisitor^ visitor) override;

		public protected:
			virtual SpanBase^ Clone() override { return ref new Strikethrough(); }
		};
	}
}