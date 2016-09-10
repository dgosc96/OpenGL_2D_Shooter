#include "Errors.h"

#include <iostream>
#include <conio.h>

void fatalError(std::string errorString) {
	std::cout << errorString << std::endl;
	std::cout << "Enter any key to quit...";
	_getch();
	exit(1);
}