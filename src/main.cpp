#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <chrono>
#include <mutex>
#include "function.h"

std::mutex waiter_waite;

void application(std::string &dish) {
	std::this_thread::sleep_for(std::chrono::seconds(rand_time(5, 5)));

	std::cout << "Order received!" << std::endl;
	dish = rand_order();
}
void kitchen(std::string &dish, std::vector<std::string> &issued) {
	int count_dish = 0;
	while (count_dish < 10) {
		std::thread waiter(application, std::ref(dish));
		waiter.join();
		waiter_waite.lock();
		std::cout << "The kitchen accepted the order " << dish << " to work!" << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(rand_time(10, 5)));
		std::cout << "--The order is ready " << dish << " is ready!--" << std::endl;
		count_dish++;
		issued.push_back(dish);
		waiter_waite.unlock();
	}
}
void courier(int& count, std::vector<std::string> &issued) {
	std::this_thread::sleep_for(std::chrono::seconds(30));
	std::cout << "\nA courier arrived and picked up " << issued.size() << " parcels!\n" << std::endl;
	count += issued.size();
	issued.clear();
}


int main() {
	std::string dish = " ";
	int count = 0;
	std::vector<std::string> issued;
	
	std::thread kitchen(kitchen, std::ref(dish), std::ref(issued));
	kitchen.detach();
	
	do {
		std::thread delivery(courier, std::ref(count), std::ref(issued));
		delivery.join();
	} while (count < 10);
	std::cout << "\n\n--The working day is over!--" << std::endl;
	return 0;
}