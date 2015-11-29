#include "JudoAcademy.h"

void JudoAcademyController::onRentButtonSelected() {
	std::cout << "rent button pressed" << std::endl;
	JudoAcademyRentView* newView = new JudoAcademyRentView();
	app->pushView(newView);
	app->pushController(new JudoAcademyRentController(newView, app));
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
	addButton = new SelectableOption('a', "Add", "Add new movie to db");
	removeButton = new SelectableOption('r', "Remove", "Remove movie from db");
	modifyButton = new SelectableOption('m', "Modify", "Modify movie");
	backButton = new SelectableOption('b', "Back", "Go back");
	addComponent(addButton);
	addComponent(removeButton);
	addComponent(modifyButton);
	addComponent(backButton);
}

JudoAcademyRentView::~JudoAcademyRentView() {
}

void JudoAcademyRentView::render(std::ostream& out) const {
	system("cls");
	out << "How may i serve u today?" << std::endl << std::endl;

	for (size_t i = 0; i < components.size(); ++i){
		components[i]->render(out);
		out << std::endl;
	}
}

void JudoAcademyRentView::update() {
	std::string line;
	std::getline(std::cin, line);

	if (line.empty()) return;

	char id = line[0];
	for (size_t i = 0; i < components.size(); ++i) {
		SelectableOption* btn = static_cast<SelectableOption*>(components[i]);
		char btnId = btn->getId();
		if (btnId == id) {
			btn->onPressed();
			return;
		}
	}
}

void JudoAcademyRentController::onAddPressed() {

}

void JudoAcademyRentController::onRemovePressed() {

}

void JudoAcademyRentController::onModifyPressed() {

}

void JudoAcademyRentController::onBackPressed() {
	app->popView();
	app->popController();
}

JudoAcademyRentController::JudoAcademyRentController(View* view, class JudoAcademy* app)
	: Controller(view, app) {
	SelectableOption* add = static_cast<SelectableOption*>(view->getComponentByName("Add"));
	SelectableOption* remove = static_cast<SelectableOption*>(view->getComponentByName("Remove"));
	SelectableOption* modify = static_cast<SelectableOption*>(view->getComponentByName("Modify"));
	SelectableOption* back = static_cast<SelectableOption*>(view->getComponentByName("Back"));
	add->setSelectionHandler(std::bind(&JudoAcademyRentController::onAddPressed, this));
	remove->setSelectionHandler(std::bind(&JudoAcademyRentController::onRemovePressed, this));
	modify->setSelectionHandler(std::bind(&JudoAcademyRentController::onRemovePressed, this));
	back->setSelectionHandler(std::bind(&JudoAcademyRentController::onBackPressed, this));
}
