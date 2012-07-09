#pragma once

#include "..\Structure\Paragraph.h"
#include "..\Structure\DocumentVisitor.h"
#include "LayoutBox.h"
#include "DWLayoutMetrics.h"

#include <sstream>
#include <stack>

namespace Prose {
	namespace Layout {
		typedef struct layout_t {
			bool success;
			bool overflowing;
			Windows::Foundation::Size finalSize;
		} layout_t;

		private class LayoutBuilder {
		public:
			LayoutBuilder(void);

			void Process(Prose::Structure::Run^ run);
			layout_t CreateLayout(LayoutBox^ box, Prose::Structure::Paragraph^ paragraph, bool requireAtLeastOne, float boxWidth, float boxHeight, float yOffset);
		private:
			void RunFormatters(Microsoft::WRL::ComPtr<IDWriteTextLayout> layout, UINT32 length);
			void ProcessInline(Prose::Structure::Inline^ inl, UINT32 length);
			Microsoft::WRL::ComPtr<IDWriteTextLayout> ConstructLayout(ComPtr<IDWriteTextFormat> baseFormat, std::wstring text);

			LayoutBox^ _box;
			bool _acceptedAtLeastOne;
			std::wstringstream _buffer;
			Platform::Collections::Vector<FormattedRange^>^ _formatters;
			Windows::Foundation::Collections::IVector<Prose::Structure::Paragraph^>^ _overflow;
			UINT32 _offset;
		};

		private ref class LayoutEngineVisitor sealed :
			public Prose::Structure::DocumentVisitor
		{
		public:
			LayoutEngineVisitor(Windows::Foundation::Size layoutSize);
	
			LayoutResult^ CreateResult(void);

			virtual void Visit(Prose::Structure::Paragraph^ paragraph) override;
			virtual void Visit(Prose::Structure::Run^ run) override;
		private:
			float _height;
			float _width;

			LayoutBox^ _currentBox;
			LayoutBuilder* _builder;

			bool _overflowing;
			LayoutTree^ _layout;

			Windows::Foundation::Collections::IVector<Prose::Structure::Paragraph^>^ _overflow;
			Windows::Foundation::Size _layoutSize;
		};
	}
}