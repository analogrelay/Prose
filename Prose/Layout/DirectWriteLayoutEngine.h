#pragma once
#include "ILayoutEngine.h"
#include "..\Structure\Paragraph.h"
#include "..\Structure\DocumentVisitor.h"

namespace Prose {
	namespace Layout {
		public ref class DirectWriteLayoutEngine sealed :
			public ILayoutEngine
		{
		public:
			virtual LayoutResult^ CreateLayout(Prose::Structure::Document^ document, Windows::Foundation::Size layoutSize);
		};

		typedef std::function<void(LayoutNode^)> layout_collector_t;

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

			bool _acceptedAtLeastOne;
			bool _overflowing;
			LayoutBox^ _currentBox;
			LayoutTree^ _layout;
			Windows::Foundation::Collections::IVector<Prose::Structure::Paragraph^>^ _overflow;
			Windows::Foundation::Size _layoutSize;
		};
	}
}