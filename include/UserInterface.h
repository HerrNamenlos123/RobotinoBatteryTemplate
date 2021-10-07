#pragma once

#include "pch.h"

extern float linearSpeed;
extern float turnSpeed;

struct FontContainer : public Battery::FontContainer {
	ImFont* font1 = ImGui::GetIO().Fonts->AddFontDefault();
};

class MyPanel : public Battery::ImGuiPanel<> {

	

public:
	MyPanel() : Battery::ImGuiPanel<>("MyPanel", { 0, 0 }, { 0, 0 }) {

	}

	void OnUpdate() override {
		size = Battery::GetMainWindow().GetSize();
	}

	void OnRender() override {
		ImGui::SliderFloat("Linear Speed", &linearSpeed, 0, 3);
		ImGui::SliderFloat("Turn Speed", &turnSpeed, 0, 3);
	}
};

class UserInterface : public Battery::ImGuiLayer<FontContainer> {
public:

	std::shared_ptr<MyPanel> panel;

	UserInterface() {}

	void OnImGuiAttach() override {
		panel = std::make_shared<MyPanel>();
		PushPanel(panel);
	}

	void OnImGuiDetach() override {

	}

	void OnImGuiUpdate() override {

	}

	void OnImGuiRender() override {

	}

	void OnImGuiEvent(Battery::Event* event) override {

	}
};
