#pragma once
#include <string>
#include <iostream>
#include <ostream>
#include <functional>
#include <vector>
#include <algorithm>

typedef std::function<void() > SelectionEventHandler;

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

class JudoAcademyRentView : public View
{
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

public:
	JudoAcademyController(View* newView, class JudoAcademy* app);
	~JudoAcademyController() = default;
};


class JudoAcademyRentController : public Controller {
public:
	JudoAcademyRentController(View* view, class JudoAcademy* app);
};

class JudoAcademy
{
private:
	View* currentView;
	Controller* currentController;
public:
	JudoAcademy()
		: currentView(new JudoAcademyView), currentController(new JudoAcademyController(currentView, this)) {}
	~JudoAcademy() = default;

	void run() {
		while (1) {
			currentView->render(std::cout);
			currentView->update();
		}
	}

	void changeView(View* newView) {
		delete currentView;
		currentView = newView;
	}

	void changeController(Controller* newController) {
		delete currentController;
		currentController = newController;
	}
};

