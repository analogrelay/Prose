#pragma once

#include "..\Structure\Paragraph.h"
#include "..\Structure\DocumentVisitor.h"
#include "LayoutBox.h"
#include "DWLayoutMetrics.h"

#include <sstream>
#include <list>

namespace Prose {
	namespace Layout {
		ref class LayoutEngineVisitor;

		private class LayoutBuilder {
		public:
			LayoutBuilder(LayoutEngineVisitor^ visitor, LayoutBox^ box, Prose::Structure::Paragraph^ paragraph);

			bool Layout(void);
			void Process(Prose::Structure::Run^ run);
			void PushFormat(Prose::TextFormat^ format);
			void PopFormat(void);
		private:
			void ProcessInline(Prose::Structure::Inline^ inl, UINT32 length);
			void ApplyFormatters(Microsoft::WRL::ComPtr<IDWriteTextLayout> layout, UINT32 length);
			Microsoft::WRL::ComPtr<IDWriteTextLayout> ConstructLayout(Microsoft::WRL::ComPtr<IDWriteTextFormat> baseFormat, std::wstring text, float boxWidth, float boxHeight);

			UINT32 _offset;
			LayoutBox^ _box;
			std::wstringstream _buffer;
			std::list<Prose::TextFormat^> _formatStack;
			LayoutEngineVisitor^ _visitor;
			Prose::Structure::Paragraph^ _paragraph;
			Platform::Collections::Vector<FormattedRange^>^ _formatters;
		};

		private ref class LayoutEngineVisitor sealed :
			public Prose::Structure::DocumentVisitor
		{
		public:
			LayoutResult^ CreateResult(void);

			LayoutEngineVisitor(Windows::Foundation::Size layoutSize);

			virtual void Visit(Prose::Structure::Run^ run) override;
			virtual void Visit(Prose::Structure::Paragraph^ paragraph) override;
			virtual void Visit(Prose::Structure::SpanBase^ span) override;
		internal:
			property float VerticalOffset {
				float get() { return _height; }
			}

			property bool CanOverflowAll {
				bool get() { return _canOverflowAll; }
			}

			Windows::Foundation::Size GetAvailableSize();

			void AddOverflow(Prose::Structure::Paragraph^ paragraph);
			void ReserveSpace(float width, float height);
		private:
			float _height;
			float _width;

			LayoutBox^ _currentBox;
			LayoutBuilder* _builder;

			bool _overflowing;
			bool _canOverflowAll;
			LayoutTree^ _layout;

			Windows::Foundation::Collections::IVector<Prose::Structure::Paragraph^>^ _overflow;
			Windows::Foundation::Size _layoutSize;
		};
	}
}