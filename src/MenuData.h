#ifndef _MENUDATA_H_
#define _MENUDATA_H_

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "ActionData.h"

typedef void (*ActionFunctionType)(ActionData& action_data);

class MenuData {
public:
	MenuData();

	void addAction(const std::string& name, ActionFunctionType func, const std::string& description);

	const std::vector<std::string>& getNames() const;

	ActionFunctionType getFunction(const std::string& name);

	const std::string& getDescription(const std::string& name);

private:
	std::vector<std::string> main_names;
	std::map<std::string, ActionFunctionType> main_functions;
	std::map<std::string, std::string> main_commands;
};

#endif /* _MENUDATA_H_ */
/* Local Variables: */
/* mode:c++ */
/* End: */
