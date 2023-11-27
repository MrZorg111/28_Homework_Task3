#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <chrono>
#include <mutex>
#include "function.h"

std::vector<std::string> order_queue;
std::vector<std::string> ready_orders;
std::mutex order, ready;

void application() {
	for (int orders = 0; orders < 10; orders++) {
		std::this_thread::sleep_for(std::chrono::seconds(rand_time(5, 5)));
		order.lock();
		std::cout << "Order received!" << std::endl;
		order_queue.push_back(rand_order());
		order.unlock();
	}
	
}
void kitchen() {
	std::string dish;
	for(int k = 0; k < 10;) {
		std::this_thread::sleep_for(std::chrono::seconds(rand_time(5, 10)));
		order.lock();
		if (!order_queue.empty()) {
			dish = order_queue.back();
			std::cout << "An order has been accepted for work: " << dish << std::endl;
			order_queue.resize(order_queue.size() - 1);
			k++;
			ready.lock();
			std::cout << "Order " << dish << " ready!" << std::endl;
			ready_orders.push_back(dish);
			ready.unlock();
		}
		order.unlock();
	}
}
void courier() {
	int delivered = 0;
	do {
		std::this_thread::sleep_for(std::chrono::seconds(30));
		ready.lock();
		if (!ready_orders.empty()) {
			std::cout << "Adopted "<< ready_orders.size() << " order for delivery!" << std::endl;
			delivered += ready_orders.size();
			ready_orders.clear();
		}
		ready.unlock();
	} while (delivered < 10);
}


int main() {
	
	std::thread appli(application);
	std::thread kit(kitchen);
	std::thread cour(courier);
	appli.join();
	kit.join();
	cour.join();

	return 0;
}