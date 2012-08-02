#pragma once

#include "Inline.h"

namespace Prose {
	namespace Structure {
		namespace WFC = Windows::Foundation::Collections;
		namespace WUX = Windows::UI::Xaml;

		ref class StructureVisitor;

		private ref class SpanBase abstract :
			public Inline
		{
		public:
			virtual property UINT32 Length { UINT32 get() override; }
			virtual InlinePair^ Split(UINT32 localOffset) override;

			virtual property WFC::IVector<Inline^>^ Inlines {
				WFC::IVector<Inline^>^ get() { 
					return _inlines;
				}
			};

			virtual void Accept(StructureVisitor^ visitor) override;

		public protected:
			virtual SpanBase^ Clone() abstract;

		private protected:
			SpanBase(void);

		private:
			WFC::IVector<Inline^>^ _inlines;
		};

		private ref class Span sealed : public SpanBase {
		public:
			Span(void) : SpanBase() {}

			virtual void Accept(StructureVisitor^ visitor) override;

		public protected:
			virtual SpanBase^ Clone() override { return ref new Span(); }
		};

		private ref class Italic sealed : public SpanBase {
		public:
			Italic(void) : SpanBase() {
				Format = ref new TextFormat();
				Format->FontStyle = Windows::UI::Text::FontStyle::Italic;
			}

			virtual void Accept(StructureVisitor^ visitor) override;

		public protected:
			virtual SpanBase^ Clone() override { return ref new Italic(); }
		};

		private ref class Bold sealed : public SpanBase {
		public:
			Bold(void) : SpanBase() {
				Format = ref new TextFormat();
				Format->FontWeight = Windows::UI::Text::FontWeights::Bold;
			}

			virtual void Accept(StructureVisitor^ visitor) override;

		public protected:
			virtual SpanBase^ Clone() override { return ref new Bold(); }
		};

		private ref class Underline sealed : public SpanBase {
		public:
			Underline(void) : SpanBase() {
				Format = ref new TextFormat();
				Format->HasUnderline = true;
			}

			virtual void Accept(StructureVisitor^ visitor) override;

		public protected:
			virtual SpanBase^ Clone() override { return ref new Underline(); }
		};

		private ref class Strikethrough sealed : public SpanBase {
		public:
			Strikethrough(void) : SpanBase() {
				Format = ref new TextFormat();
				Format->HasStrikethrough = true;
			}

			virtual void Accept(StructureVisitor^ visitor) override;

		public protected:
			virtual SpanBase^ Clone() override { return ref new Strikethrough(); }
		};
	}
}