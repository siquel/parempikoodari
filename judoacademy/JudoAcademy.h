#pragma once
#include <string>
#include <iostream>
#include <ostream>
class Renderable {
public:
	virtual void render(std::ostream&) const = 0 ;
};

class SelectableOption : public Renderable {
private:
	char id = '\0';
	std::string name;
	std::string description;
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
public:
	JudoAcademyView() 
		: rentButton('r', "Rent", "Do you fancy renting judo movies?"),
		managementButton('m', "Manage", "Do you fancy managing judo movies?") {}

	~JudoAcademyView() = default;

	virtual void render(std::ostream& out) const override {
		out << "Welcome to JudoAcademy management console!" << std::endl << std::endl;
		out << rentButton << std::endl << managementButton << std::endl;
	}
};

class JudoAcademy
{
public:
	JudoAcademy();
	~JudoAcademy();
};

