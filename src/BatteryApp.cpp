
#include "pch.h"
#include "BatteryApp.h"

float linearSpeed = 0.3f;
float turnSpeed = 0.3f;

BatteryApp::BatteryApp() : Battery::Application(600, 600) {
	LOG_SET_LOGLEVEL(BATTERY_LOG_LEVEL_DEBUG);
}

bool BatteryApp::OnStartup() {

	ui = std::make_shared<UserInterface>();
	PushOverlay(ui);
	robotino.Connect("192.168.0.1");

	LOG_DEBUG("Application loaded");
	return true;
}

void BatteryApp::OnUpdate() {
	float x = (GetKey(ALLEGRO_KEY_DOWN) ? -linearSpeed : 0) + (GetKey(ALLEGRO_KEY_UP) ? linearSpeed : 0);
	float y = (GetKey(ALLEGRO_KEY_LEFT) ? linearSpeed : 0) + (GetKey(ALLEGRO_KEY_RIGHT) ? -linearSpeed : 0);
	float omega = (GetKey(ALLEGRO_KEY_PGUP) ? turnSpeed : 0) + (GetKey(ALLEGRO_KEY_PGDN) ? -turnSpeed : 0);
	robotino.DriveDirect(x, y, omega);
}

void BatteryApp::OnRender() {
	/*double time = Battery::TimeUtils::GetRuntime();
	auto image = robotino.GetCamera();
	//Battery::TimeUtils::Sleep(0.01);
	double elapsed = Battery::TimeUtils::GetRuntime() - time;

	LOG_INFO("Time elapsed: {:04f}s", elapsed);

	//auto image = Robotino::Image();
	//image.create(200, 200, { 0, 255, 0 });
	/*if (image.valid) {
		Battery::Texture2D texture;
		texture.CreateBitmap(image.width, image.height, ALLEGRO_MEMORY_BITMAP);
		al_set_target_bitmap(texture.GetAllegroBitmap());
		al_lock_bitmap(texture.GetAllegroBitmap(), 0, 0);
		for (size_t x = 0; x < image.width; x += 1) {
			for (size_t y = 0; y < image.height; y += 1) {
				auto color = image.get(x, y);
				//al_put_pixel((int)x, (int)y, Battery::Graphics::ConvertAllegroColor((glm::vec3)(color.r, color.g, color.b)));
				//al_draw_pixel((int)x, (int)y, Battery::Graphics::ConvertAllegroColor((glm::vec3)(color.r, color.g, color.b)));
				al_draw_pixel((int)x, (int)y, al_map_rgb(color.r, color.g, color.b));
			}
		}
		al_unlock_bitmap(texture.GetAllegroBitmap());
		al_set_target_backbuffer(window.allegroDisplayPointer);
		al_draw_bitmap(texture.GetAllegroBitmap(), 0, 0, 0);
	}*/
}

void BatteryApp::OnShutdown() {
	robotino.Disconnect();
}

void BatteryApp::OnEvent(Battery::Event* e) {
	if (e->GetType() == Battery::EventType::WindowClose) {
		CloseApplication();
	}
}

Battery::Application* Battery::CreateApplication() {
	return new BatteryApp();
}
