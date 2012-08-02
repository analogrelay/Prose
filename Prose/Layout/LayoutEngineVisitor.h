#pragma once

#include "..\Structure\Paragraph.h"
#include "..\Structure\StructureVisitor.h"
#include "LayoutBox.h"
#include "DWLayoutMetrics.h"
#include "..\Structure\Span.h"

#include <sstream>
#include <list>

namespace Prose {
	namespace Layout {
		namespace PS = Prose::Structure;
		namespace PlC = Platform::Collections;
		namespace MW = Microsoft::WRL;
		namespace WF = Windows::Foundation;
		namespace WFC = Windows::Foundation::Collections;

		ref class LayoutEngineVisitor;

		private class LayoutBuilder {
		public:
			LayoutBuilder(LayoutEngineVisitor^ visitor, LayoutBox^ box, PS::Paragraph^ paragraph);

			bool Layout(void);
			void Process(PS::Run^ run);
			void PushFormat(Prose::TextFormat^ format);
			void PopFormat(void);
		private:
			void ProcessInline(PS::Inline^ inl, UINT32 length);
			void ApplyFormatters(MW::ComPtr<IDWriteTextLayout> layout, UINT32 length);
			MW::ComPtr<IDWriteTextLayout> ConstructLayout(MW::ComPtr<IDWriteTextFormat> baseFormat, std::wstring text, float boxWidth, float boxHeight);

			UINT32 _offset;
			LayoutBox^ _box;
			std::wstringstream _buffer;
			std::list<Prose::TextFormat^> _formatStack;
			LayoutEngineVisitor^ _visitor;
			PS::Paragraph^ _paragraph;
			PlC::Vector<FormattedRange^>^ _formatters;
		};

		private ref class LayoutEngineVisitor :
			public PS::StructureVisitor
		{
		public:
			LayoutResult^ CreateResult(void);

			virtual void Visit(PS::Run^ run) override;
			virtual void Visit(PS::Paragraph^ paragraph) override;
			virtual void Visit(PS::SpanBase^ span) override;
		internal:
			LayoutEngineVisitor(WF::Size layoutSize);

			property float VerticalOffset {
				float get() { return _height; }
			}

			property bool CanOverflowAll {
				bool get() { return _canOverflowAll; }
			}

			WF::Size GetAvailableSize();

			void AddOverflow(PS::Paragraph^ paragraph);
			void ReserveSpace(float width, float height);
		private:
			float _height;
			float _width;

			LayoutBox^ _currentBox;
			LayoutBuilder* _builder;

			bool _overflowing;
			bool _canOverflowAll;
			LayoutTree^ _layout;

			WFC::IVector<PS::Paragraph^>^ _overflow;
			WF::Size _layoutSize;
		};
	}
}