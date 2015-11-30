#include "view.h"
#include "app.h"
#include "util.h"
#include <algorithm>
namespace crm {
	namespace ui {
		View::View(App* app) 
			: app(app) {

		}

		View::~View() {
			std::for_each(options.begin(), options.end(), [](Option* option) {
				delete option;
			});
		}

		void View::addOption(Option* option) {
			options.push_back(option);
		}

		Option* View::getOptionByName(const std::string& optionName) {
			auto it = std::find_if(options.begin(), options.end(), [&optionName](Option* option) {
				return option->getName() == optionName;
			});

			if (it == options.end()) return nullptr;

			return *it;
		}

		MainView::MainView(App* app)
			: View(app){
			options.push_back(new Option('a', "Add"));
			options.push_back(new Option('l', "Load"));
			options.push_back(new Option('x', "Exit"));
		}

		void MainView::render() const {
			std::for_each(options.begin(), options.end(), [](Option* option) {
				std::cout << option->getId() << " - " << option->getName() << std::endl;
			});
		}

		void MainView::update() {
			std::cout << "" << std::endl;
			char pick = util::getInputFromConsoleWithText<char>("What do you want to do ?");

			auto it = std::find_if(options.begin(), options.end(), [pick](Option* option) {
				return option->getId() == pick;
			});
			// invalid
			if (it == options.end()) return;
			// callback
			(*it)->fireEvent();
		}

		Option::Option(char id, const std::string& name) 
			: id(id), name(name) {

		}

		void Option::fireEvent() {
			onPressed();
		}

	}
}