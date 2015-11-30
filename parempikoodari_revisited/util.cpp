#include "util.h"
#include <tinyxml2.h>
#include <algorithm>

namespace crm {
	namespace util {

		void serializeToXML(const std::string& path, const user::UserData& info) {
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

		void deserializeFromXML(const std::string& path, std::vector<user::UserData>& out) {
			using namespace tinyxml2;
			XMLDocument doc;

			doc.LoadFile(path.c_str());
			XMLNode* root = nullptr;
			if ((root = doc.FirstChild()) == nullptr) {
				return;
			}
			for (XMLElement* child = root->FirstChildElement(); child != nullptr; child = child->NextSiblingElement()) {
				
				std::string name = child->Attribute("name");
				std::string surname = child->Attribute("surname");
				std::string email = child->Attribute("email");
				size_t age = atoi(child->Attribute("age"));
				out.push_back(user::UserData{ name, surname, email, age });
			}
		}

		void printUsers(const std::vector<user::UserData>& users) {
			std::for_each(users.begin(), users.end(), [](const user::UserData& user) {
				std::cout << user.name << " | " << user.surname << std::endl;
			});
		}

	}
}