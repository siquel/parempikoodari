#pragma once
#include <string>

namespace crm {
	namespace user {
		struct UserData {
			std::string name;
			std::string surname;
			std::string email;
			size_t age;
		};
	}
}