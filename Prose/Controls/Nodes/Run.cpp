#include "pch.h"
#include "Run.h"
#include "Structure\RunNode.h"

using namespace Prose;
using namespace Prose::Controls;
using namespace Prose::Structure;

using namespace Windows::UI::Xaml;

DependencyProperty^ Run::_TextProperty = RegisterDP("Text", Platform::String::typeid, Run::typeid);

Run::Run(void) { }

InlineNode^ Run::ConstructStructureNode() {
	auto run = ref new RunNode();
	run->Format = CreateFormat();
	run->Text = Text;
	return run;
}