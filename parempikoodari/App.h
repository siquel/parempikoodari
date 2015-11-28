#pragma once
#include <string>
#include <map>
#include <functional>

typedef std::function<void() > AppCallback;
typedef std::map<char, AppCallback> CallbackContainer;
struct Userinfo;

class App
{
public:
	App();
	~App();
	void start() ;
private:
	bool running;
	CallbackContainer callbacks;
	void saveToXML(const std::string& path, const Userinfo&) const;
	void intro() ;
	void addUser();
	void loadUsers();
	void exit();
};

struct Userinfo {
	std::string name;
	std::string surname;
	std::string email;
	size_t age;
};
