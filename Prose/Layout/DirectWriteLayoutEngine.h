#pragma once
#include "ILayoutEngine.h"
#include "..\Structure\DocumentVisitor.h"

namespace Prose {
	namespace Layout {
		public ref class DirectWriteLayoutEngine sealed :
			public ILayoutEngine
		{
		public:
			virtual LayoutTree^ CreateLayout(Prose::Structure::Document^ document, Windows::Foundation::Size layoutSize);
		};

		typedef std::function<void(LayoutNode^)> layout_collector_t;

		private ref class LayoutEngineVisitor sealed :
			public Prose::Structure::DocumentVisitor
		{
		public:
			property LayoutTree^ FinalLayout {
				LayoutTree^ get() { return _layout; }
			}

			LayoutEngineVisitor(Windows::Foundation::Size layoutSize);
	
			virtual void Visit(Prose::Structure::Paragraph^ paragraph) override;
			virtual void Visit(Prose::Structure::Run^ run) override;
		private:
			void CalculateLayout(Box^ box);

			layout_collector_t _collector;
			LayoutTree^ _layout;
			Windows::Foundation::Size _layoutSize;
		};
	}
}