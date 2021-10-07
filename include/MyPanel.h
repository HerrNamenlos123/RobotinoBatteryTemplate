#pragma once

#include "pch.h"
#include "BatteryApp.h"
#include "Fonts.h"

#include "RobotinoLayer.h"

class MyPanel : public Battery::ImGuiPanel<> {
public:

	// Here you can store data which is specific to this panel

	MyPanel() : Battery::ImGuiPanel<>("MyPanel", { 0, 0 }, { 400, 0 }) {	// Specify a unique name and the position and size of the panel

	}

	void OnUpdate() override {	// Called every frame before render, only for calculations

		size.y = Battery::GetMainWindow().GetSize().y;	// This continually overwrites the vertical size with the vertical window size
														// -> Panel always spans across the entire window height when the window is resized
	}

	void OnRender() override {	// Called every frame after update, this is within an ImGui window -> call ImGui widgets directly
		auto fonts = GetFontContainer<FontContainer>();		// Here you can access the fonts from Fonts.h
		
		ImGui::PushFont(fonts->font1);
		
		if (ImGui::Button("My Button")) {
			LOG_INFO("My Button was pressed!");
		}

		auto& app = BatteryApp::Get();				// You can access your own app class from BatteryApp.h like this
		if (app.robotinoLayer) {					// You can only access the layer's contents if it exists
			ImGui::SliderFloat("Linear speed", &app.robotinoLayer->linearSpeed, 0, 3);		// Accessing the variables from the Robotino Layer
			ImGui::SliderFloat("Turn speed", &app.robotinoLayer->turnSpeed, 0, 3);
		}

		ImGui::PopFont();
	}
};
