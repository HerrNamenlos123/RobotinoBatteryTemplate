
#include "pch.h"
#include "UserInterface.h"

class BatteryApp : public Battery::Application {

	std::shared_ptr<UserInterface> ui;
	Robotino::Robotino robotino;

public:
	BatteryApp();

	bool OnStartup() override;
	void OnUpdate() override;
	void OnRender() override;
	void OnShutdown() override;
	void OnEvent(Battery::Event* e) override;

};
