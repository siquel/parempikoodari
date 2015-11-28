#pragma once
#include <string>
#include <iostream>
#include <ostream>
#include <functional>


typedef std::function<void() > SelectionEventHandler;

class Renderable {
public:
	virtual void render(std::ostream&) const = 0 ;
};



class SelectableOption : public Renderable {
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

	inline void setName(const std::string& newName) {
		name = newName;
	}

	inline void setDescription(const std::string& newDesc) {
		description = newDesc;
	}

	inline const std::string& getName() const {
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

class JudoAcademyView : public Renderable
{
private:
	SelectableOption rentButton;
	SelectableOption managementButton;
	SelectableOption* buttons[2];
public:
	JudoAcademyView() 
		: rentButton('r', "Rent", "Do you fancy renting judo movies?"),
		managementButton('m', "Manage", "Do you fancy managing judo movies?") {
		buttons[0] = &rentButton;
		buttons[1] = &managementButton;
	}

	~JudoAcademyView() = default;

	virtual void render(std::ostream& out) const override {
		system("CLS");
		out << "Welcome to JudoAcademy management console!" << std::endl << std::endl;
		out << rentButton << std::endl << managementButton << std::endl;
	}

	inline SelectableOption& getRentButton() {
		return rentButton;
	}

	inline SelectableOption& getManagementButton() {
		return managementButton;
	}

	void update() {
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
};

class JudoAcademyController {
private:
	JudoAcademyView& view;

	void onRentButtonSelected() {
		std::cout << "rent button pressed" << std::endl;
	}

	void onManagementButtonSelected() {
		std::cout << "rent button pressed" << std::endl;
	}

public:
	JudoAcademyController(JudoAcademyView& view) 
		: view(view) {
		view.getRentButton().setSelectionHandler(std::bind(&JudoAcademyController::onRentButtonSelected, this));
		view.getManagementButton().setSelectionHandler(std::bind(&JudoAcademyController::onManagementButtonSelected, this));
	}
	~JudoAcademyController() = default;
};

class JudoAcademy
{
private:
	JudoAcademyView view;
	JudoAcademyController controller;
public:
	JudoAcademy()
		: controller(view) {}
	~JudoAcademy() = default;

	void run() {
		while (1) {
			view.render(std::cout);
			view.update();
		}
	}
};

