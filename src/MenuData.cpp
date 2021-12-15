#include "MenuData.h"
#include <string>
#include <map>

MenuData::MenuData() {
}

void MenuData::addAction(const std::string& name, ActionFunctionType func, const std::string& description) {
	//append the name to the collection of names
	//insert func in the action functjion map (same name as the key and inter description into the description the map with name as the key
	main_names.push_back(name);
	main_functions[name] = func;
	main_commands[name] = description;
}

const std::vector<std::string>& MenuData::getNames() const {
	//return the name collection data member
	return main_names;
}


ActionFunctionType MenuData::getFunction(const std::string& name) {
	//if name is a key in the action function map, return the function associated with it. 
	//if ame is not a key, return 0
	//use .containsValue()
	if(main_functions.find(name) != main_functions.end()) {
		return main_functions[name];
	} else {
		return 0;
	}
}

const std::string& MenuData::getDescription(const std::string& name) {
	//if name is a key in the description map, return description
	//else return empty string -> use static std::string var that is init to ""
	if(main_commands.find(name) != main_commands.end()) {
		return main_commands[name];
	}
	static std::string empty = "";
	return empty;
}
