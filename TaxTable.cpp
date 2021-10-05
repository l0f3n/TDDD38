#include <iostream>
#include <iomanip>

int main() {
	std::cout << "INPUT PART" << std::endl;
	std::cout << "==========" << std::endl;

	std::cout << "Enter first price: ";
	float first_price;
	std::cin >> first_price;

	std::cout << "Enter last price : ";
	float last_price;
	std::cin >> last_price;

	std::cout << "Enter stride     : ";
	float stride;
	std::cin >> stride;

	std::cout << "Enter tax percent: ";
	float tax_percent;
	std::cin >> tax_percent;
	tax_percent = tax_percent / 100;

	std::cout << "\nTAX TABLE" << std::endl;
	std::cout << "=========" << std::endl;

	std::cout << "       Price              Tax      Price with tax" << std::endl;
	std::cout << "-------------------------------------------------" << std::endl;

	std::cout << std::right << std::fixed << std::setprecision(2) << std::showpoint;
	
	float price = first_price;
	while (price <= last_price) {
		float tax = price*tax_percent;

		std::cout << std::setw(12) << price;
		std::cout << std::setw(17) << tax; 
		std::cout << std::setw(20) << price + tax << std::endl;

		price += stride;
	} 

	return 0;
}
