#pragma once

#include "Item.h"

class ItemGroup{
private:
	Item item;
	int count;

public:
	ItemGroup(Item item):
		item(item),
		count(1){}

	Item getItem() const{
		return item;
	}

	int getCount() const{
		return count;
	}

	double getSubtotal() const{
		return item.getPrice() * count * item.getDiscount();
	}

	double getSave() const{
		return item.getPrice() * count * (1 - item.getDiscount());
	}

	void accumulate(){
		count++;
	}
};