#pragma once
#include <string>
#include <iostream>
#include <ostream>
#include <functional>
#include <vector>
#include <algorithm>
#include <queue>

typedef std::function<void() > SelectionEventHandler;

enum Format {
	DVD,
	Bluray,
	VHS
};

class MovieModel {
private:
	std::string name;
	std::string description;
	size_t year;
	double price;
	Format format;
public:
	MovieModel(const std::string& name, const std::string& description, const size_t year, const double price, Format fmt);
	~MovieModel() = default;

	inline void setName(const std::string& newName) {
		name = newName;
	}

	inline void setYear(const size_t newYear) {
		year = newYear;
	}

	inline void setDescription(const std::string& newDesc) {
		description = newDesc;
	}

	inline void setPrice(const double newPrice) {
		price = newPrice;
	}

	inline const Format getFormat() const {
		return format;
	}

	inline const std::string& getName() const {
		return name;
	}

	inline const std::string& getDescription() const {
		return description;
	}

	inline const size_t getYear() const {
		return year;
	}

	inline const double getPrice() const {
		return price;
	}

	inline std::string getFormatString() const {
		switch (format)
		{
		case DVD:
			return "DVD";
			break;
		case Bluray:
			return "Bluray";
			break;
		case VHS:
			return "VHS";
			break;
		default:
			return "";
			break;
		}
	}
};

class Renderable {
public:
	virtual void render(std::ostream&) const = 0 ;
};

class Component : public Renderable {
public:
	virtual void setName(const std::string& newName) = 0;
	virtual const std::string& getName() const = 0;
};

class View : public Renderable {
protected:
	typedef std::vector<Component*>::const_iterator ComponentIterator;
	typedef std::vector<Component*> ComponentCollection;
	ComponentCollection components;
public:
	virtual ~View() {
		std::for_each(components.begin(), components.end(), [](Component* c){
			delete c;
		});
	}

	virtual void update() = 0;
	void addComponent(Component* newComponent) {
		components.push_back(newComponent);
	}

	Component* getComponentByName(const std::string& componentName) const {
		ComponentIterator found = std::find_if(components.begin(), components.end(), [&componentName](Component* c) {
			return c->getName() == componentName;
		});
		if (found == components.end()) return nullptr;

		return *found;
	}

	const ComponentCollection& getComponents() const {
		return components;
	}
};

class BasicView : public View {
public:
	virtual void update();
	virtual void render(std::ostream&) const;
};


class SelectableOption : public Component {
private:
	char id = '\0';
	std::string name;
	std::string description;
	SelectionEventHandler handle;
public:
	SelectableOption(char id, const std::string& name, const std::string& description)
		: id(id), name(name), description(description) { }
	SelectableOption() = default;
	~SelectableOption() = default;

	virtual void render(std::ostream& out) const override {
		out << "   " << id << ").    - " << name << " - " << description;
	}

	inline void setId(const char newId) {
		id = newId;
	}

	inline void setName(const std::string& newName) override {
		name = newName;
	}

	inline void setDescription(const std::string& newDesc) {
		description = newDesc;
	}

	inline const std::string& getName() const override {
		return name;
	}

	inline const std::string& getDescription() const {
		return name;
	}

	inline const char getId() const {
		return id;
	}
	
	inline void setSelectionHandler(SelectionEventHandler handle) {
		this->handle = handle;
	}

	inline void onPressed() {
		if (handle != nullptr) {
			handle();
		}
	}
};

inline std::ostream& operator<<(std::ostream& os, const SelectableOption& obj) {
	obj.render(os);
	return os;
}

inline std::ostream& operator<<(std::ostream& os, const MovieModel& model) {
	os << model.getName()
		<< " | " << model.getFormatString() << " | Year: " << model.getYear()
		<< " | Price: " << model.getPrice();
	return os;
}

inline bool operator==(const MovieModel& a, const MovieModel& b) {
	if (&a == &b) return true;
	return a.getName() == b.getName() &&
		a.getPrice() == b.getPrice() &&
		a.getYear() == b.getYear() &&
		a.getFormat() == b.getFormat() &&
		a.getDescription() == b.getDescription();
}

class JudoAcademyView :  public BasicView
{
private:
public:
	JudoAcademyView();

	~JudoAcademyView();

	virtual void render(std::ostream& out) const override;

	void update() override;
};

class JudoAcademyMovieEditView : public BasicView {
private:
	MovieModel* model;
public:
	JudoAcademyMovieEditView(MovieModel* model);
	~JudoAcademyMovieEditView();
	virtual void render(std::ostream& out) const override;

	void update() override;
};

class JudoAcademyManageView : public BasicView
{
private:
	SelectableOption* addButton;
	SelectableOption* removeButton;
	SelectableOption* modifyButton;
	SelectableOption* backButton;
public:
	JudoAcademyManageView();

	~JudoAcademyManageView();

	virtual void render(std::ostream& out) const override;

	void update() override;
};

class JudoAcademyRentView : public BasicView {
private:
public:
	JudoAcademyRentView();
	~JudoAcademyRentView();
	virtual void render(std::ostream& out) const override;

	void update() override;
};

class Controller {
protected:
	class JudoAcademy* app;
	View* view;
	Controller(View* view, class JudoAcademy* app);
public:
	virtual ~Controller() {}

};

class JudoAcademyController : public Controller {
private:
	void onRentButtonSelected();
	void onManagementButtonSelected();
	void onExitButtonSelected();
public:
	JudoAcademyController(View* newView, class JudoAcademy* app);
	~JudoAcademyController() = default;
};


class JudoAcademyManageController : public Controller {
private:
	void onAddPressed();
	void onRemovePressed();
	void onModifyPressed();
	void onBackPressed();
public:
	JudoAcademyManageController(View* view, class JudoAcademy* app);
};

class JudoAcademyMovieEditController : public Controller {
private:
	MovieModel* model;
	void onBackPressed();
	void onEditNamePressed();
	void onEditYearPressed();
	void onEditPricePressed();
	void onEditDescriptionPressed();
public:
	JudoAcademyMovieEditController(View* view, class JudoAcademy* app, MovieModel* model);
};

class JudoAcademyRentController : public Controller {
private:	
	void onBackPressed();
	void onHirePressed();
	void onReturnPressed();
public:
	JudoAcademyRentController(View* view, class JudoAcademy* app);
};

class Storage {
private:
	typedef std::vector<MovieModel> MovieCollection;
	typedef std::vector<std::tuple<size_t, size_t>> Stock;
	MovieCollection& database;
	Stock stock;
	size_t getIndexOf(const MovieModel& model) const;
	void get(size_t index, size_t& currentlyInStock, size_t& total) const;
public:
	Storage(MovieCollection& database);

	size_t currentlyInStock(const MovieModel& movieInStock) const;
	size_t getTotalCopies(const MovieModel& ofMovie) const;
	bool isAvailable(const MovieModel& movie) const;
	void rent(const MovieModel& movie);
	size_t howManyCurrentlyRented(const MovieModel& movieToCheck) const;
	void setStorageCount(const MovieModel& model, size_t totalCount);
	void createStorage(size_t totalCount);
};

class JudoAcademy
{
private:
	typedef std::vector<MovieModel> MovieCollection;
	std::vector<View*> views;
	std::vector<Controller*> controllers;
	MovieCollection database;
	Storage storage;
	std::queue<std::string> errors;

	bool running;
	inline void getMoviesByPredicate(std::function<bool(MovieModel&)> predicate, std::vector<MovieModel>& out) {
		std::for_each(database.begin(), database.end(), [&out, predicate](MovieModel& model){
			if (predicate(model)) out.push_back(model);
		});	
	}
public:
	JudoAcademy() : running(false), storage(database) {
		View* view = new JudoAcademyView;
		Controller* controller = new JudoAcademyController(view, this);
		views.push_back(view);
		controllers.push_back(controller);
	}
	~JudoAcademy() = default;

	void stop() {
		running = false;
	}

	void raiseError(const std::string& errorString) {
		errors.push(errorString);
	}

	void run() {
		running = true;
		while (running) {
			views.back()->render(std::cout);
			// usually render clears the console, so flash errors after render
			while (errors.size()) {
				std::cerr << "\t" << errors.front() << std::endl;
				errors.pop();
			}
			views.back()->update();
		}
	}

	inline Storage& getStorage() {
		return storage;
	}

	inline MovieCollection& getMovies() {
		return database;
	}

	inline void addMovie(const MovieModel& movie, size_t total) {
		database.push_back(movie);
		storage.createStorage(total);
	}

	inline MovieModel* getMovieByName(const std::string& name) {
		return nullptr;
	}

	inline MovieModel* getMovieByIndex(const size_t index) {
		return &database[index];
	}

	inline void getMoviesByFormat(const Format format, MovieCollection& to) {
		getMoviesByPredicate([format](MovieModel& model){
			return model.getFormat() == format;
		}, to);
	}

	void pushView(View* view) {
		views.push_back(view);
	}

	void popView() {
		delete views.back();
		views.pop_back();
	}

	void popController() {
		delete controllers.back();
		controllers.pop_back();
	}

	void pushController(Controller* newController) {
		controllers.push_back(newController);
	}

};

