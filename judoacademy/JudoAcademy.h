#pragma once
#include <string>
#include <iostream>
#include <ostream>
#include <functional>
#include <vector>
#include <algorithm>

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

class JudoAcademyView :  public View
{
private:
	SelectableOption* buttons[2];
public:
	JudoAcademyView();

	~JudoAcademyView();

	virtual void render(std::ostream& out) const override;

	void update() override;
};

class JudoAcademyManageView : public View
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

class JudoAcademy
{
private:
	typedef std::vector<MovieModel> MovieCollection;
	std::vector<View*> views;
	std::vector<Controller*> controllers;
	MovieCollection database;

	inline void getMoviesByPredicate(std::function<bool(MovieModel&)> predicate, std::vector<MovieModel>& out) {
		std::for_each(database.begin(), database.end(), [&out, predicate](MovieModel& model){
			if (predicate(model)) out.push_back(model);
		});	
	}
public:
	JudoAcademy() {
		View* view = new JudoAcademyView;
		Controller* controller = new JudoAcademyController(view, this);
		views.push_back(view);
		controllers.push_back(controller);
	}
	~JudoAcademy() = default;

	void run() {
		while (1) {
			views.back()->render(std::cout);
			views.back()->update();
		}
	}

	inline MovieCollection& getMovies() {
		return database;
	}

	inline void addMovie(const MovieModel& movie) {
		database.push_back(movie);
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

