#pragma once
#include "forward_declare.h"

CRM_FORWARD_DECLARE_2(crm, ui, View);
CRM_FORWARD_DECLARE_1(crm, App);

namespace crm {
	namespace controller {
		class CRMController {
		private:
			ui::View* view;
			App* app;
			void onAdd();
			void onLoad();
			void exit();
		public:
			CRMController(ui::View*, App*);
			~CRMController();
		};
	}
}