#include "JudoAcademy.h"

void JudoAcademyController::onRentButtonSelected() {
	std::cout << "rent button pressed" << std::endl;

}

void JudoAcademyController::onManagementButtonSelected() {
	std::cout << "manage button pressed" << std::endl;
	JudoAcademyManageView* newView = new JudoAcademyManageView();
	app->pushView(newView);
	app->pushController(new JudoAcademyManageController(newView, app));
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

JudoAcademyManageView::JudoAcademyManageView() {
	addButton = new SelectableOption('a', "Add", "Add new movie to db");
	removeButton = new SelectableOption('r', "Remove", "Remove movie from db");
	modifyButton = new SelectableOption('m', "Modify", "Modify movie");
	backButton = new SelectableOption('b', "Back", "Go back");
	addComponent(addButton);
	addComponent(removeButton);
	addComponent(modifyButton);
	addComponent(backButton);
}

JudoAcademyManageView::~JudoAcademyManageView() {
}

void JudoAcademyManageView::render(std::ostream& out) const {
	system("cls");
	out << "How may i serve u today?" << std::endl << std::endl;

	for (size_t i = 0; i < components.size(); ++i){
		components[i]->render(out);
		out << std::endl;
	}
}

void JudoAcademyManageView::update() {
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

void JudoAcademyManageController::onAddPressed() {
	system("CLS");
	std::cout << "Adding new movie..." << std::endl;

	std::string name, description;
	size_t year, format;
	double price;

	std::cout << "Name: ";
	std::getline(std::cin, name);
	std::cout << std::endl;
	std::cout << "Description:";
	std::getline(std::cin, description);
	std::cout << std::endl << "Year: ";
	std::cin >> year;
	std::cout << std::endl << "Price: ";
	std::cin >> price;
	
	
	do {
		std::cout << "Is this DVD (" << Format::DVD << "), " << "Bluray (" << Bluray
			<< ") or " << "VHS (" << VHS << "): ";
		std::cin >> format;
	} while (format < DVD || format > VHS);

	app->addMovie(MovieModel(name, description, year, price, static_cast<Format>(format)));
}

void JudoAcademyManageController::onRemovePressed() {

}

void JudoAcademyManageController::onModifyPressed() {
	std::cout << "Select movie id which to modify: " << std::endl << std::endl;
	std::vector<MovieModel>& movies = app->getMovies();

	for (size_t i = 0; i < movies.size(); ++i) {
		std::cout << i << "). --- " << movies[i].getName() << std::endl;
	}
	size_t index = 0;
	std::cin >> index;
}

void JudoAcademyManageController::onBackPressed() {
	app->popView();
	app->popController();
}

JudoAcademyManageController::JudoAcademyManageController(View* view, class JudoAcademy* app)
	: Controller(view, app) {
	SelectableOption* add = static_cast<SelectableOption*>(view->getComponentByName("Add"));
	SelectableOption* remove = static_cast<SelectableOption*>(view->getComponentByName("Remove"));
	SelectableOption* modify = static_cast<SelectableOption*>(view->getComponentByName("Modify"));
	SelectableOption* back = static_cast<SelectableOption*>(view->getComponentByName("Back"));
	add->setSelectionHandler(std::bind(&JudoAcademyManageController::onAddPressed, this));
	remove->setSelectionHandler(std::bind(&JudoAcademyManageController::onRemovePressed, this));
	modify->setSelectionHandler(std::bind(&JudoAcademyManageController::onModifyPressed, this));
	back->setSelectionHandler(std::bind(&JudoAcademyManageController::onBackPressed, this));
}

MovieModel::MovieModel(const std::string& name, const std::string& description, const size_t year, const double price, Format fmt)
	: name(name), description(description), year(year), price(price), format(fmt) {

}
