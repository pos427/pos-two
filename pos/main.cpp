#include <json\reader.h>
#include <json\value.h>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <string>
#include <cassert>
#include <iomanip>
#include "Item.h"
#include "ItemGroup.h"

using uint = Json::Value::UInt;
using Counter = std::unordered_map < std::string, ItemGroup > ;

void output(Counter c, std::ostream& os);

int main(){
	Json::Reader reader;
	Json::Value value;

	std::ifstream cart;
	cart.open("cart.json");

	reader.parse(cart, value);

	Counter counter; //dummy
	
	assert(value.isArray());
	
	for (int i = 0; value.isValidIndex(i); i++){
		//std::cout << value[uint(i)]["name"].asString() << "\n";
		Json::Value jsi = value[uint(i)];
		Item item{
			jsi["barcode"].asString(),
			jsi["name"].asString(),
			jsi["unit"].asString(),
			jsi["price"].asDouble(),
			jsi["discount"].asDouble()
		};

		auto r = counter.find(item.getBarcode());

		if (r == counter.end()){
			ItemGroup itemgroup{ item };

			counter.insert(std::make_pair(item.getBarcode() , itemgroup));
		}
		else{
			ItemGroup& itemGroup = r->second;
			itemGroup.accumulate();
		}

	}

	output(counter, std::cout);

	system("pause");
}

void output(Counter c, std::ostream& os){
	os << "*****商店购物清单*****\n";
	double total = 0;
	double savingTotal = 0;
	for (auto iter = c.begin(); iter != c.end(); iter++){
		ItemGroup& ig = iter->second;
		os
			<< "名称:" << ig.getItem().getName() << ", "
			<< "数量:" << ig.getCount() << ig.getItem().getUnit() << ", "
			<< "单价:" << std::fixed << std::setprecision(2) << std::setfill('0') << ig.getItem().getPrice() << "(元), "
			<< "小计:" << ig.getSubtotal() << "(元)"
			<< "\n";

		total += ig.getSubtotal();
		savingTotal += ig.getSave();
	}
	os << "----------------------\n"
		<< "总计:" << total << "元\n"
		<< "节省:" << savingTotal << "元\n"
		<< "**********************\n";


}
