#include "pch.h"
#include "DirectWriteLayoutEngine.h"
#include "LayoutEngineVisitor.h"

using namespace Prose::Structure;
using namespace Prose::Layout;

LayoutResult^ DirectWriteLayoutEngine::CreateLayout(StructureTree^ tree, Windows::Foundation::Size layoutSize) {
	auto visitor = ref new LayoutEngineVisitor(layoutSize);
	tree->Accept(visitor);
	return visitor->CreateResult();
}