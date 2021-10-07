#pragma once

#include "pch.h"

struct FontContainer : public Battery::FontContainer {

	// Here you can load any number of fonts to be used throughout the application
	ImFont* font1 = ImGui::GetIO().Fonts->AddFontDefault();

};
