#include "pch.h"
#include "Helpers.h"

bool operator==(Windows::UI::Text::FontWeight left, Windows::UI::Text::FontWeight right) {
	return left.Weight == right.Weight;
};

bool operator!=(Windows::UI::Text::FontWeight left, Windows::UI::Text::FontWeight right) {
	return left.Weight != right.Weight;
};