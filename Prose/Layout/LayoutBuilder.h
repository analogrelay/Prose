#pragma once

#include "FormatStack.h"
#include "LayoutBox.h"
#include "Structure\BlockNode.h"

#include <sstream>

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
			LayoutBuilder(LayoutEngineVisitor^ visitor, LayoutBox^ box, PS::BlockNode^ BlockNode, FormatStack^ formatStack);

			bool Layout(void);
			void Process(PS::RunNode^ run);
		private:
			void ProcessInline(PS::InlineNode^ inl, UINT32 length);
			void ApplyFormatters(MW::ComPtr<IDWriteTextLayout> layout, UINT32 length);
			MW::ComPtr<IDWriteTextLayout> ConstructLayout(MW::ComPtr<IDWriteTextFormat> baseFormat, std::wstring text, float boxWidth, float boxHeight);

			UINT32 _offset;
			LayoutBox^ _box;
			FormatStack^ _formatStack;
			std::wstringstream _buffer;
			LayoutEngineVisitor^ _visitor;
			PS::BlockNode^ _block;
			PlC::Vector<FormattedRange^>^ _formatters;
		};
	}
}