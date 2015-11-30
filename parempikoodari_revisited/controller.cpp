#include "controller.h"
#include "view.h"
#include "util.h"
#include "app.h"

namespace crm {
	namespace controller {

		void CRMController::onAdd() {

		}

		void CRMController::onLoad() {

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