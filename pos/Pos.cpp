#include <string>
#include <json\reader.h>
#include <json\value.h>
#include <fstream>
#include <unordered_map>
#include "ItemGroup.h"
#include <cassert>
#include "CartInfo.h"

using uint = Json::Value::UInt;
using Counter = std::unordered_map < std::string, ItemGroup >;

class Pos{
public:

	CartInfo parse(std::string filePath){
		std::ifstream cart;
		cart.open(filePath);
		return parse(cart);
	}

	CartInfo parse(std::istream& is){
		Json::Reader reader;
		Json::Value value;

		reader.parse(is, value);

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

				counter.insert(std::make_pair(item.getBarcode(), itemgroup));
			}
			else{
				ItemGroup& itemGroup = r->second;
				itemGroup.accumulate();
			}

		}
		std::vector<ItemGroup> vi;
		for (auto kp : counter){
			vi.push_back(kp.second);
		}
		return vi;
	}

};