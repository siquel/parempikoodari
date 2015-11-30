#include "app.h"
#include "view.h"
#include "controller.h"

namespace crm {

	App::App() 
		: running(false), 
		view(new ui::MainView(this)), 
		controller(new controller::CRMController(view, this)) {

	}

	App::~App() {
		delete view;
		delete controller;
	}

	void App::start() {
		// dont allow start again
		if (running) return;

		running = true;

		while (running) {
			view->render();
			view->update();
		}
	}

	void App::stop() {
		running = false;
	}

}