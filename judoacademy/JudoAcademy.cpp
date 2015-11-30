#include "JudoAcademy.h"

#define JUDO_CALLBACK_0(__selector__, __target__,...)   std::bind(&__selector__,__target__, ##__VA_ARGS__)

#define BIND_FUNC_TO_COMPONENT(view, name, selector, target) \
(static_cast<SelectableOption*>(view->getComponentByName(name)))->setSelectionHandler(\
	JUDO_CALLBACK_0(selector, target))

void JudoAcademyController::onRentButtonSelected() {
	JudoAcademyRentView* view = new JudoAcademyRentView();
	JudoAcademyRentController* controller = new JudoAcademyRentController(view, app);
	app->pushView(view);
	app->pushController(controller);
}

void JudoAcademyController::onManagementButtonSelected() {
	std::cout << "manage button pressed" << std::endl;
	JudoAcademyManageView* newView = new JudoAcademyManageView();
	app->pushView(newView);
	app->pushController(new JudoAcademyManageController(newView, app));
}


void JudoAcademyController::onExitButtonSelected() {
	app->stop();
}

Controller::Controller(View* view, JudoAcademy* app)
	:view(view), app(app) {

}

JudoAcademyController::JudoAcademyController(View* newView, JudoAcademy* app)
	: Controller(newView, app) {
	BIND_FUNC_TO_COMPONENT(view, "Rent", JudoAcademyController::onRentButtonSelected, this);
	BIND_FUNC_TO_COMPONENT(view, "Manage", JudoAcademyController::onManagementButtonSelected, this);
	BIND_FUNC_TO_COMPONENT(view, "Exit", JudoAcademyController::onExitButtonSelected, this);
}


JudoAcademyView::JudoAcademyView()  {
	SelectableOption* rent = new SelectableOption('r', "Rent", "Do you fancy renting judo movies?");
	SelectableOption* manage = new SelectableOption('m', "Manage", "Do you fancy managing judo movies?");
	SelectableOption* exit = new SelectableOption('x', "Exit", "Exit app");
	addComponent(rent);
	addComponent(manage);
	addComponent(exit);
}

JudoAcademyView::~JudoAcademyView() {

}

void JudoAcademyView::render(std::ostream& out) const {
	system("CLS");
	out << "Welcome to JudoAcademy management console!" << std::endl << std::endl;
	BasicView::render(out);
}

void JudoAcademyView::update() {
	BasicView::update();
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

	BasicView::render(out);
}

void JudoAcademyManageView::update() {
	BasicView::update();
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
	size_t index = 0;
	std::vector<MovieModel>& movies = app->getMovies();

	// if we dont have movies, just go back
	if (movies.empty()) {
		app->raiseError("No movies!");
		return;
	}

	do {
		system("cls");
		std::cout << "Select movie id which to modify: " << std::endl << std::endl;
		

		for (size_t i = 0; i < movies.size(); ++i) {
			MovieModel& model = movies[i];
			std::cout << i << "). --- " << model << std::endl;
		}

		std::cin >> index;
	} while (index > movies.size());

	MovieModel& model = movies[index];
	
	JudoAcademyMovieEditView* view = new JudoAcademyMovieEditView(&model);
	JudoAcademyMovieEditController* controller = new JudoAcademyMovieEditController(view, app, &model);
	app->pushView(view);
	app->pushController(controller);
}

void JudoAcademyManageController::onBackPressed() {
	app->popView();
	app->popController();
}

JudoAcademyManageController::JudoAcademyManageController(View* view, class JudoAcademy* app)
	: Controller(view, app) {
	BIND_FUNC_TO_COMPONENT(view, "Add", JudoAcademyManageController::onAddPressed, this);
	BIND_FUNC_TO_COMPONENT(view, "Remove", JudoAcademyManageController::onRemovePressed, this);
	BIND_FUNC_TO_COMPONENT(view, "Modify", JudoAcademyManageController::onModifyPressed, this);
	BIND_FUNC_TO_COMPONENT(view, "Back", JudoAcademyManageController::onBackPressed, this);
}

MovieModel::MovieModel(const std::string& name, const std::string& description, const size_t year, const double price, Format fmt)
	: name(name), description(description), year(year), price(price), format(fmt) {

}

JudoAcademyMovieEditView::JudoAcademyMovieEditView(MovieModel* model) 
	:model(model) {
	SelectableOption* name = new SelectableOption('n', "Edit name", "Edit movie name");
	SelectableOption* desc = new SelectableOption('d', "Edit description", "Edit movie description");
	SelectableOption* year = new SelectableOption('y', "Edit year", "Edit movie year");
	SelectableOption* price = new SelectableOption('p', "Edit price", "Edit movie price");
	SelectableOption* back = new SelectableOption('b', "Back", "Go back");
	addComponent(name);
	addComponent(desc);
	addComponent(year);
	addComponent(price);
	addComponent(back);
}

JudoAcademyMovieEditView::~JudoAcademyMovieEditView() {

}

void JudoAcademyMovieEditView::render(std::ostream& out) const {
	system("cls");
	std::cout << "Editing " << model->getName() << std::endl;
	BasicView::render(out);
}

void JudoAcademyMovieEditView::update() {
	BasicView::update();
}

void BasicView::update() {
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

void BasicView::render(std::ostream& out) const {
	for (size_t i = 0; i < components.size(); ++i){
		components[i]->render(out);
		out << std::endl;
	}
}

void JudoAcademyMovieEditController::onBackPressed() {
	app->popView();
	app->popController();
}

template <class T>
T getInput(const char* displayName, const T& currentValue) {
	std::cout << "Current " << displayName << ": " << currentValue << ". Enter new " << displayName << ": ";
	T newValue;
	std::cin >> newValue;
	return newValue;
}

template <>
std::string getInput(const char* displayName, const std::string& currentValue) {
	std::cout << "Current " << displayName << ": " << currentValue << ". Enter new " << displayName << ": ";
	std::string newValue;
	std::getline(std::cin, newValue);
	return newValue;
}

void JudoAcademyMovieEditController::onEditNamePressed() {
	system("CLS");
	model->setName(getInput<std::string>("name", model->getName()));
}

void JudoAcademyMovieEditController::onEditYearPressed() {
	system("CLS");
	model->setYear(getInput("year", model->getYear()));
}

void JudoAcademyMovieEditController::onEditPricePressed() {
	system("CLS");
	model->setPrice(getInput("price", model->getPrice()));
}

void JudoAcademyMovieEditController::onEditDescriptionPressed() {
	system("CLS");
	model->setDescription(getInput("description", model->getDescription()));
}

JudoAcademyMovieEditController::JudoAcademyMovieEditController(View* view, JudoAcademy* app, MovieModel* model)
	: Controller(view, app), model(model) {
	BIND_FUNC_TO_COMPONENT(view, "Edit name", JudoAcademyMovieEditController::onEditNamePressed, this);
	BIND_FUNC_TO_COMPONENT(view, "Edit year", JudoAcademyMovieEditController::onEditYearPressed, this);
	BIND_FUNC_TO_COMPONENT(view, "Edit price", JudoAcademyMovieEditController::onEditPricePressed, this);
	BIND_FUNC_TO_COMPONENT(view, "Edit description", JudoAcademyMovieEditController::onEditDescriptionPressed, this);
	BIND_FUNC_TO_COMPONENT(view, "Back", JudoAcademyMovieEditController::onBackPressed, this);
}

JudoAcademyRentView::JudoAcademyRentView() {
	addComponent(new SelectableOption('h', "Hire", "Hire movie"));
	addComponent(new SelectableOption('r', "Return", "Return movie"));
	addComponent(new SelectableOption('b', "Back", "Go back"));
}

JudoAcademyRentView::~JudoAcademyRentView() {

}

void JudoAcademyRentView::render(std::ostream& out) const {
	system("CLS");
	out << "Welcome to renting service!" << std::endl << std::endl;
	BasicView::render(out);
}

void JudoAcademyRentView::update() {
	BasicView::update();
}

void JudoAcademyRentController::onBackPressed() {
	app->popView();
	app->popController();
}

void JudoAcademyRentController::onHirePressed() {
	system("CLS");
	size_t i = 0;
	std::string line;
	std::vector<MovieModel>& movies = app->getMovies();

	if (movies.empty()) {
		app->raiseError("No movies to hire!");
		return;
	}
	
	std::for_each(movies.begin(), movies.end(), [&i](MovieModel& model) {
		std::cout << i++ << "). " << model << std::endl;
	});
	std::cout << "Select movie you want to hire: ";
	std::getline(std::cin, line);
}

void JudoAcademyRentController::onReturnPressed() {

}

JudoAcademyRentController::JudoAcademyRentController(View* view, JudoAcademy* app)
	: Controller(view, app) {
	BIND_FUNC_TO_COMPONENT(view, "Hire", JudoAcademyRentController::onHirePressed, this);
	BIND_FUNC_TO_COMPONENT(view, "Return", JudoAcademyRentController::onReturnPressed, this);
	BIND_FUNC_TO_COMPONENT(view, "Back", JudoAcademyRentController::onBackPressed, this);
}
