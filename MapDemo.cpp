// MapDemo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <map>
#include <string>
#include <iostream>
using std::map;
using std::string;
using std::cout;

void printMap(map<string, int> m) {
	for (auto pair : m) {
		cout << " [ " << pair.first << " , " << pair.second << " ] " << "\n";
	}
}

void demoForMap() {
	map<string, int> price{ {"Apple",3} };

	price.insert({ "Banana",1 });
	price["Avocado"] = 10;
	printMap(price);

	cout << "\nErasing...\n";
	auto it = price.begin();
	price.erase(it);
	printMap(price);
	cout << "\n";

	price.erase("Banada");
	printMap(price);

	cout << "\nClearing...\n";
	price.clear();
}

int main()
{
	demoForMap();
    return 0;
}

