#pragma once

#include "forward_declare.h"

CRM_FORWARD_DECLARE_2(crm, ui, View);
CRM_FORWARD_DECLARE_2(crm, controller, CRMController);

namespace crm {
	class App {
	private:
		bool running;
		ui::View* view;
		controller::CRMController* controller;
	public:
		App();
		~App();
		void start();
		void stop();
	};
}