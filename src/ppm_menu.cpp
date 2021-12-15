#include "ActionData.h"
#include "MenuData.h"
#include "image_menu.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iostream>

int main() {
	std::srand(std::time(0));
	return imageMenu(std::cin, std::cout);
}
