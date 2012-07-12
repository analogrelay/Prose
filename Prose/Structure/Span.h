#pragma once

#include "Inline.h"

namespace Prose {
	namespace Structure {
		ref class DocumentVisitor;

		[Windows::UI::Xaml::Markup::ContentProperty(Name = "Inlines")]
		public ref class SpanBase :
			public Inline
		{
		public:
			virtual property UINT32 Length { UINT32 get() override; }
			virtual InlinePair^ Split(UINT32 localOffset) override;

			property Windows::Foundation::Collections::IVector<Inline^>^ Inlines {
				Windows::Foundation::Collections::IVector<Inline^>^ get() { 
					return _inlines;
				}
			};

			virtual void Accept(DocumentVisitor^ visitor) override;

		public protected:
			virtual SpanBase^ Clone() { throw ref new Platform::NotImplementedException("SpanBase.Clone must be implemented by subclasses of SpanBase"); };

		private protected:
			SpanBase(void) : _inlines(ref new Platform::Collections::Vector<Inline^>()) {}

		private:
			Windows::Foundation::Collections::IVector<Inline^>^ _inlines;
		};

		public ref class Span sealed : public SpanBase {
		public:
			Span(void) : SpanBase() {}

			virtual void Accept(DocumentVisitor^ visitor) override;

		public protected:
			virtual SpanBase^ Clone() override { return ref new Span(); }
		};

		public ref class Italic sealed : public SpanBase {
		public:
			Italic(void) : SpanBase() {
				FontStyle = Windows::UI::Text::FontStyle::Italic;
			}

			virtual void Accept(DocumentVisitor^ visitor) override;

		public protected:
			virtual SpanBase^ Clone() override { return ref new Italic(); }
		};

		public ref class Bold sealed : public SpanBase {
		public:
			Bold(void) : SpanBase() {
				FontWeight = Windows::UI::Text::FontWeights::Bold;
			}

			virtual void Accept(DocumentVisitor^ visitor) override;

		public protected:
			virtual SpanBase^ Clone() override { return ref new Bold(); }
		};

		public ref class Underline sealed : public SpanBase {
		public:
			Underline(void) : SpanBase() {
				this->HasUnderline = true;
			}

			virtual void Accept(DocumentVisitor^ visitor) override;

		public protected:
			virtual SpanBase^ Clone() override { return ref new Underline(); }
		};

		public ref class Strikethrough sealed : public SpanBase {
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