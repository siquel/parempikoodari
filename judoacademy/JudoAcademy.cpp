#include "JudoAcademy.h"

void JudoAcademyController::onRentButtonSelected() {
	std::cout << "rent button pressed" << std::endl;
	JudoAcademyRentView* newView = new JudoAcademyRentView();
	app->changeView(newView);
	app->changeController(new JudoAcademyRentController(newView, app));
}

void JudoAcademyController::onManagementButtonSelected() {
	std::cout << "rent button pressed" << std::endl;
}


Controller::Controller(View* view, JudoAcademy* app)
	:view(view), app(app) {

}

JudoAcademyController::JudoAcademyController(View* newView, JudoAcademy* app)
	: Controller(newView, app) {
	SelectableOption* rentButton = static_cast<SelectableOption*>(view->getComponentByName("Rent"));
	SelectableOption* manageButton = static_cast<SelectableOption*>(view->getComponentByName("Manage"));
	rentButton->setSelectionHandler(std::bind(&JudoAcademyController::onRentButtonSelected, this));
	manageButton->setSelectionHandler(std::bind(&JudoAcademyController::onManagementButtonSelected, this));
}


JudoAcademyView::JudoAcademyView()  {
	SelectableOption* rent = new SelectableOption('r', "Rent", "Do you fancy renting judo movies?");
	SelectableOption* manage = new SelectableOption('m', "Manage", "Do you fancy managing judo movies?");
	addComponent(rent);
	addComponent(manage);
	buttons[0] = rent;
	buttons[1] = manage;

}

JudoAcademyView::~JudoAcademyView() {

}

void JudoAcademyView::render(std::ostream& out) const {
	system("CLS");
	out << "Welcome to JudoAcademy management console!" << std::endl << std::endl;
	for (size_t i = 0; i < components.size(); ++i){
		components[i]->render(out);
		out << std::endl;
	}
}

void JudoAcademyView::update() {
	std::string line;
	std::getline(std::cin, line);
	if (line.empty()) return;

	char id = line[0];
	for (size_t i = 0; i < 2; ++i) {
		SelectableOption* btn = buttons[i];
		char btnId = btn->getId();
		if (btnId == id) {
			btn->onPressed();
			return;
		}
	}
}

JudoAcademyRentView::JudoAcademyRentView() {

}

JudoAcademyRentView::~JudoAcademyRentView() {
}

void JudoAcademyRentView::render(std::ostream& out) const {
	std::cout << "RENT" << std::endl;
}

void JudoAcademyRentView::update() {

}

JudoAcademyRentController::JudoAcademyRentController(View* view, class JudoAcademy* app) 
	:Controller(view, app) {

}
