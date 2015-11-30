#pragma once

#include <string>
#include <iostream>
#include <functional>

#define CRM_CALLBACK(s, t, ...) std::bind(&s, t, ##__VA_ARGS__)

namespace crm {
	namespace util {
		void saveToXML(const std::string& path);

		template <class T>
		inline T getInputFromConsoleWithText(const std::string& displayString) {
			T output;
			std::cout << displayString << ": ";
			std::cin >> output;
			std::cout << std::endl;
			return output;
		}

		// we need to use getline again
		template <>
		inline std::string getInputFromConsoleWithText(const std::string& displayString) {
			std::string output;
			std::cout << displayString << ": ";
			std::cin >> output;
			std::cout << std::endl;
			return output;
		}
	}
}