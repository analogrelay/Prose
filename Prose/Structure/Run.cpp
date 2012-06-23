#include "pch.h"
#include "Run.h"

using namespace Prose::Structure;

Run::Run(void) {}
Run::Run(Platform::String^ text) {
	Text = text;
}