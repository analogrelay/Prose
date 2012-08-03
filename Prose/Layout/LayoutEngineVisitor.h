#pragma once

#include "Structure\ParagraphNode.h"
#include "Structure\StructureVisitor.h"
#include "Structure\SpanNode.h"
#include "LayoutBox.h"
#include "DWLayoutMetrics.h"
#include "LayoutBuilder.h"
#include "LayoutResult.h"
#include "FormatStack.h"

#include <sstream>
#include <list>

namespace Prose {
	namespace Layout {
		namespace PS = Prose::Structure;
		namespace PlC = Platform::Collections;
		namespace MW = Microsoft::WRL;
		namespace WF = Windows::Foundation;
		namespace WFC = Windows::Foundation::Collections;

		private ref class LayoutEngineVisitor :
			public PS::StructureVisitor
		{
		public:
			LayoutResult^ CreateResult(void);

			virtual void Visit(PS::StructureTree^ tree) override;
			virtual void Visit(PS::RunNode^ run) override;
			virtual void Visit(PS::BlockNode^ BlockNode) override;
			virtual void Visit(PS::SpanNode^ span) override;
		internal:
			LayoutEngineVisitor(WF::Size layoutSize);

			property float VerticalOffset {
				float get() { return _height; }
			}

			property bool CanOverflowAll {
				bool get() { return _canOverflowAll; }
			}

			WF::Size GetAvailableSize();

			void AddOverflow(PS::BlockNode^ BlockNode);
			void ReserveSpace(float width, float height);
		private:
			float _height;
			float _width;

			LayoutBox^ _currentBox;
			LayoutBuilder* _builder;

			bool _overflowing;
			bool _canOverflowAll;
			LayoutTree^ _layout;
			FormatStack^ _formatStack;

			WFC::IVector<PS::BlockNode^>^ _overflow;
			WF::Size _layoutSize;
		};
	}
}