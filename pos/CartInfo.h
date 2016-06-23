#pragma once

#include <vector>
#include "ItemGroup.h"
#include <sstream>
#include <iomanip>

class CartInfo{
private:
	std::vector<ItemGroup> itemgroups;

public:
	CartInfo(std::vector<ItemGroup> igs) : itemgroups(igs){};
	
	double getTotal() const{
		double total = 0;
		for (auto iter = itemgroups.cbegin(); iter != itemgroups.cend(); iter++){
			const ItemGroup& ig = *iter;
			total += ig.getSubtotal();
		}
		return total;
	}

	double getSaved() const{
		double total = 0;
		for (auto iter = itemgroups.cbegin(); iter != itemgroups.cend(); iter++){
			const ItemGroup& ig = *iter;
			total += ig.getSave();
		}
		return total;
	}

	std::string generateReport(){
		
		std::ostringstream ostr{};

		ostr << "*****商店购物清单*****\n";
		for (auto iter = itemgroups.begin(); iter != itemgroups.end(); iter++){
			ItemGroup& ig = *iter;
			ostr
				<< "名称:" << ig.getItem().getName() << ", "
				<< "数量:" << ig.getCount() << ig.getItem().getUnit() << ", "
				<< "单价:" << std::fixed << std::setprecision(2) << std::setfill('0') << ig.getItem().getPrice() << "(元), "
				<< "小计:" << ig.getSubtotal() << "(元)"
				<< "\n";
		}
		ostr << "----------------------\n"
			<< "总计:" << getTotal() << "元\n"
			<< "节省:" << getSaved() << "元\n"
			<< "**********************\n";

		return ostr.str();
	}
};