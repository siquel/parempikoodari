#include "App.h"
#include <tinyxml2.h>
#include <iostream>
App::App() : running(false) {
}


App::~App() {
}


void App::start()  {
	running = true;
	callbacks['a'] = std::bind(&App::addUser, this);
	callbacks['l'] = std::bind(&App::loadUsers, this);
	callbacks['x'] = std::bind(&App::exit, this);
	intro();

}

void App::saveToXML(const std::string& path, const Userinfo& info) const {
	using namespace tinyxml2;

	XMLDocument doc;

	doc.LoadFile(path.c_str());
	XMLNode* root = nullptr;
	// if the root doesnt exist
	if ((root = doc.FirstChildElement("users")) == nullptr) {
		root = doc.NewElement("users");
		doc.InsertFirstChild(root);
	}

	XMLElement* user = doc.NewElement("user");
	user->SetAttribute("name", info.name.c_str());
	user->SetAttribute("surname", info.surname.c_str());
	user->SetAttribute("email", info.email.c_str());
	user->SetAttribute("age", info.age);
	root->InsertEndChild(user);
	doc.SaveFile(path.c_str());
}

void App::intro()  {
	std::string input;

	do {
		std::cout << "a) add user" << std::endl;
		std::cout << "l) load users" << std::endl;
		std::cout << "x) exit" << std::endl;
		std::getline(std::cin,input);
		
		if (input.size() > 1 || callbacks.find(input[0]) == callbacks.end()) {
			std::cout << "invalid option" << std::endl << std::endl;
			continue;
		}
		
		callbacks.at(input[0])();
	} while (running);
}

void App::addUser() {
	std::string input;
	Userinfo info;

	std::cout << "fname: ";
	std::getline(std::cin, input);
	info.name = input;
	std::cout << std::endl;

	std::cout << "surname: ";
	std::getline(std::cin, input);
	info.surname = input;
	std::cout << std::endl;

	std::cout << "email: ";
	std::getline(std::cin, input);
	info.email = input;
	std::cout << std::endl;

	std::cout << "age: ";
	std::getline(std::cin, input);
	info.age = atoi(input.c_str());
	std::cout << std::endl;

	saveToXML(std::string("asd.xml"), info);
}

void App::loadUsers() {
	using namespace tinyxml2;
	XMLDocument doc;

	doc.LoadFile("asd.xml");
	XMLNode* root = nullptr;
	if ((root = doc.FirstChild()) == nullptr) {
		std::cout << "no users" << std::endl;
		return;
	}
	for (XMLElement* child = root->FirstChildElement(); child != nullptr; child = child->NextSiblingElement()) {
		std::cout << "-------" << std::endl;
		std::cout << child->Attribute("name") << " " 
			<< child->Attribute("surname") << ", "
			<< child->Attribute("email") << ", "
			<< child->Attribute("age") << " years old" << std::endl;
		std::cout << "-------" << std::endl;
	}
}

void App::exit() {
	running = false;
}
