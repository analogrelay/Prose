#include "pch.h"
#include "RenderingPlan.h"

using namespace Prose::Rendering;

RenderingPlan::RenderingPlan(void) : _surfaces(ref new Platform::Collections::Vector<RenderSurface^>()) { }