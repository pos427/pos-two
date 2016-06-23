
#include <iostream>
#include <string>
#include "Item.h"
#include "pos.cpp"


int main(int argc, char** argv){
	
	Pos pos{};
	CartInfo ci = pos.parse(argv[1]);
	std::cout << ci.generateReport();

	system("pause");
}

