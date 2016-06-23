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

		ostr << "*****�̵깺���嵥*****\n";
		for (auto iter = itemgroups.begin(); iter != itemgroups.end(); iter++){
			ItemGroup& ig = *iter;
			ostr
				<< "����:" << ig.getItem().getName() << ", "
				<< "����:" << ig.getCount() << ig.getItem().getUnit() << ", "
				<< "����:" << std::fixed << std::setprecision(2) << std::setfill('0') << ig.getItem().getPrice() << "(Ԫ), "
				<< "С��:" << ig.getSubtotal() << "(Ԫ)"
				<< "\n";
		}
		ostr << "----------------------\n"
			<< "�ܼ�:" << getTotal() << "Ԫ\n"
			<< "��ʡ:" << getSaved() << "Ԫ\n"
			<< "**********************\n";

		return ostr.str();
	}
};