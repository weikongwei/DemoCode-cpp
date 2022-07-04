// VectorDemo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
using std::cout;
using std::endl;


void printVector(std::vector<int> & vec_val) {
	cout << "Vector values: \n";

	//Looping method 1
	//for (size_t i; i < vec_val.size(); i++) {
	//	cout << vec_val.at(i);
	//}

	//Looping Mehtod 2
	for (auto num : vec_val) {
		cout << num << " ";
	}

	cout << endl << endl;
}

void vectorDemo() {
	std::vector<int> vec;

	// Initializing vector
	cout << "\n\n\n"
		 << "*******************\n"
		 << "Initializing vector\n"
		 << "*******************\n\n";
	vec = { 1,2,3,4,5 };
	cout << "Vector of ";
	printVector(vec);

	// Push (Vector only supports push_back)
	cout << "\n\n\n" 
		<< "*******************\n"
		<< "**** Push back ****\n"
		<< "*******************\n\n";
	vec.push_back(6);
	printVector(vec);

	// Pop (Vector only supports pop_back)
	cout << "\n\n\n"
		<< "*******************\n"
		<< "**** Pop back *****\n"
		<< "*******************\n\n";
	vec.pop_back();
	printVector(vec);

	// Insert
	cout << "\n\n\n"
		<< "*******************\n"
		<< "* Insert at Front *\n"
		<< "*******************\n\n";
	auto it = vec.begin();
	vec.insert(it,0);
	printVector(vec);

	// Emplace
	cout << "\n\n\n"
		<< "*******************\n"
		<< "* Emplace at Front *\n"
		<< "*******************\n\n";
	it++;
	vec.emplace(it, 9);
	printVector(vec);

	// Erase
	cout << "\n\n\n"
		<< "*******************\n"
		<< "  Erase the Front \n"
		<< "*******************\n\n";
	it = vec.begin();
	vec.erase(it);
	printVector(vec);

	// Clear
	cout << "\n\n\n"
		<< "*******************\n"
		<< "  Clear the Vector \n"
		<< "*******************\n\n";
	vec.clear();
	printVector(vec);

}


int main()
{
	vectorDemo();
    return 0;
}

