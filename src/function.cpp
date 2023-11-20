#include <iostream>
#include <ctime>
#include "function.h"

int rand_time(int vol, int step) {
	srand(std::time(nullptr));

	return rand() % vol + step;
}


std::string rand_order() {
	srand(std::time(nullptr));

	switch (rand() % 5 + 1) {
	case 1:
		return "Pizza";
		break;
	case 2:
		return "Soup";
		break;
	case 3:
		return "Steak";
		break;
	case 4:
		return "Salad";
		break;
	case 5:
		return "Sushi";
		break;
	default:
		std::cout << "Ошибка рандомайзера блюд!" << std::endl;
	}
}