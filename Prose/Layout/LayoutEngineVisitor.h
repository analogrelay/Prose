#pragma once

#include "..\Structure\Paragraph.h"
#include "..\Structure\DocumentVisitor.h"
#include "LayoutBox.h"

#include <sstream>
#include <stack>

namespace Prose {
	namespace Layout {
		private class LayoutBuilder {
		public:
			LayoutBuilder(void);

			void Process(Prose::Structure::Run^ run);
			void AddFormatter(format_action_t format, UINT32 start_position, UINT32 length);
			Microsoft::WRL::ComPtr<IDWriteTextLayout> CreateLayout(Microsoft::WRL::ComPtr<IDWriteTextFormat> baseFormat, FLOAT boxWidth, FLOAT boxHeight);
			Microsoft::WRL::ComPtr<IDWriteTextLayout> Reformat(std::wstring newString, Microsoft::WRL::ComPtr<IDWriteTextFormat> baseFormat, FLOAT boxWidth, FLOAT boxHeight);
			void ApplyMetrics(DWLayoutMetrics^ metrics);

			std::wstring Str();
		private:
			std::wstringstream _buffer;
			std::vector<format_operation_t> _formatters;
			UINT32 _offset;

			void RunFormatters(Microsoft::WRL::ComPtr<IDWriteTextLayout> layout, UINT32 length);
			void ProcessInline(Prose::Structure::Inline^ inl, UINT32 length);
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

			bool CalculateLayout(LayoutBox^ box, Prose::Structure::Paragraph^ paragraph);

			LayoutBox^ _currentBox;
			LayoutBuilder* _builder;

			bool _acceptedAtLeastOne;
			bool _overflowing;
			LayoutTree^ _layout;

			Windows::Foundation::Collections::IVector<Prose::Structure::Paragraph^>^ _overflow;
			Windows::Foundation::Size _layoutSize;
		};
	}
}