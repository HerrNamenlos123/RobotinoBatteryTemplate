#pragma once

#include "pch.h"

class RobotinoLayer : public Battery::Layer {
public:

	// Here you can store data which is specific to the Robotino Layer
	Robotino::Robotino robotino;
	std::string hostname = "172.26.1.1";

	float linearSpeed = 0.3f;
	float turnSpeed = 0.3f;

	void OnAttach() override {		// Called once on startup
		robotino.Connect(hostname);
	}

	void OnDetach() override {		// Called once on shutdown
		robotino.Disconnect();
	}

	void OnUpdate() override {		// Called every frame before render, only for calculations
		float x = (Battery::GetApp().GetKey(ALLEGRO_KEY_DOWN) ? -linearSpeed : 0) + (Battery::GetApp().GetKey(ALLEGRO_KEY_UP) ? linearSpeed : 0);
		float y = (Battery::GetApp().GetKey(ALLEGRO_KEY_LEFT) ? linearSpeed : 0) + (Battery::GetApp().GetKey(ALLEGRO_KEY_RIGHT) ? -linearSpeed : 0);
		float omega = (Battery::GetApp().GetKey(ALLEGRO_KEY_PGUP) ? turnSpeed : 0) + (Battery::GetApp().GetKey(ALLEGRO_KEY_PGDN) ? -turnSpeed : 0);
		robotino.DriveDirect(x, y, omega);

		if (robotino.GetBumper()) {
			robotino.DriveDirect(0, 0, 0);
			Battery::ShowWarningMessageBox("Aua du Wixa");
		}
	}

	void OnRender() override {		// Called every frame after update, render graphics here

	}

	void OnEvent(Battery::Event* event) override {		// Called when an event arrives which wasn't handled yet by the layer above

	}

	RobotinoLayer() {}
};
