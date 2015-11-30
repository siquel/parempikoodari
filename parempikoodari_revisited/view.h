#pragma once
#include "forward_declare.h"
#include <string>
#include <functional>
#include <vector>

CRM_FORWARD_DECLARE_1(crm, App);

namespace crm {
	namespace ui {

		typedef std::function<void()> SelectionEvent;

		class Option {
		private:
			char id;
			std::string name;
			SelectionEvent onPressed;
		public:
			Option(char, const std::string&);

			inline const std::string& getName() const {
				return name;
			}

			inline const char getId() const {
				return id;
			}

			inline void setEventHandler(SelectionEvent cb) {
				onPressed = cb;
			}

			void fireEvent();
		};

		class View {
		protected:
			App* app;
			std::vector<Option*> options;
		public:
			View(App* app);
			virtual ~View();
			virtual void render() const = 0;
			virtual void update() = 0;
			void addOption(Option*);
			Option* getOptionByName(const std::string&);
		};

		class MainView : public View {
		public:
			MainView(App* app);
			virtual void render() const;
			virtual void update();
		};

	}
}