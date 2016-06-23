#pragma once
#include <string>

class Item{
private:
	std::string barcode;
	std::string name;
	std::string unit;
	double price;
	double discount;

public:
	Item(std::string barcode,
		std::string name,
		std::string unit,
		double price,
		double discount) :

		barcode(barcode),
		name(name),
		unit(unit),
		price(price),
		discount(discount == 0 ? 1 : discount)
	{}

	std::string getBarcode() const { return barcode; }
	std::string getName() const { return name; }
	std::string getUnit() const { return unit; }
	float getPrice() const { return price; }
	float getDiscount() const { return discount; }

};