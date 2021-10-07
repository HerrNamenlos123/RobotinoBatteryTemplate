#pragma once

#include "pch.h"

// Forward declare your layers here
class UserInterface;
class RobotinoLayer;

class BatteryApp : public Battery::Application {
public:

	// Here you can specify various application layers
	std::shared_ptr<UserInterface> ui;
	std::shared_ptr<RobotinoLayer> robotinoLayer;

	BatteryApp();

	bool OnStartup() override;
	void OnUpdate() override;
	void OnRender() override;
	void OnShutdown() override;
	void OnEvent(Battery::Event* e) override;

	static BatteryApp& Get();

};
