#include "pch.h"
#include "DirectWriteLayoutEngine.h"
#include "LayoutEngineVisitor.h"

using namespace Prose::Structure;
using namespace Prose::Layout;

LayoutResult^ DirectWriteLayoutEngine::CreateLayout(StructureTree^ tree, Windows::Foundation::Size layoutSize, Prose::TextFormat^ baseFormat) {
	auto visitor = ref new LayoutEngineVisitor(layoutSize, baseFormat);
	tree->Accept(visitor);
	return visitor->CreateResult();
}