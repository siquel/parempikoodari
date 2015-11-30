#include "controller.h"
#include "view.h"
#include "util.h"
#include "app.h"
#include "configuration.h"
#include "user_data.h"
#include <string>

namespace crm {
	namespace controller {

		void CRMController::onAdd() {
			using namespace crm::user;
			UserData data;
			data.name = util::getInputFromConsoleWithText<std::string>("Enter first name");
			data.surname = util::getInputFromConsoleWithText<std::string>("Enter surname");
			data.email = util::getInputFromConsoleWithText<std::string>("Enter email");
			data.age = util::getInputFromConsoleWithText<size_t>("Enter age");
			util::serializeToXML(conf::PathToDataFile, data);
		}

		void CRMController::onLoad() {
			std::vector<user::UserData> users;
			util::deserializeFromXML(conf::PathToDataFile, users);
			util::printUsers(users);
		}

		void CRMController::exit() {
			app->stop();
		}

		CRMController::CRMController(ui::View* view, App* app)
			: view(view), app(app) {
			view->getOptionByName("Load")->setEventHandler(CRM_CALLBACK(CRMController::onLoad, this));
			view->getOptionByName("Add")->setEventHandler(CRM_CALLBACK(CRMController::onAdd, this));
			view->getOptionByName("Exit")->setEventHandler(CRM_CALLBACK(CRMController::exit, this));
		}

		CRMController::~CRMController() {

		}

	}
}