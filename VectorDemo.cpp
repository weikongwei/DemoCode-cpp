// VectorDemo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <string>
#include <iterator>

using std::cout;
using std::endl;
using std::string;
using std::vector;

class BankAccount {
private:
	string owner;
	int accountNum;
	double balance;

public:
	BankAccount(){}
	BankAccount(const string & owner_val, double balance_val, int accountNum_val) {
		owner = owner_val;
		balance = balance_val;
		accountNum = accountNum_val;

		printf("Account added. \n");
		printf("Account number: %05d\n", accountNum);
		printf("Owner: %s \n", owner.c_str());
		printf("Balance: %0.2f\n\n", balance);
	}

	BankAccount(const BankAccount & source) {
		owner = source.owner;
		accountNum = source.accountNum;
		balance = source.balance;
		printf("A copy of account %05d created.\n", accountNum);
	}
	~BankAccount() {
		printf("\n Destructor called for %05d.\n\n", accountNum);
	}

	// Methods
	void setOwner(const string & name) {
		owner = name;
		printf("Owner name added: %s \n", owner.c_str());
	}

	void setAccountNumb(int accountNum_val) {
		accountNum = accountNum_val;
		printf("Account number set to %05d\n", accountNum);
	}

	void setBalance(double balance_val) {
		balance = balance_val;
	}

	void deposit(double depo) {
		balance += depo;
		printf("Deposited %.2f dollars\n", depo);
	}

	bool withdraw(double withdrw) {
		if (withdrw >= balance) {
			cout << "Insufficient fund. Withdraw faild. " << endl << endl;
			return false;
		}
		else
		{
			balance -= withdrw;
			cout << "Withdraw success. " << endl
				<< "New balance: " << balance << endl << endl;
			return true;
		}
	}

	const string & getOwner() const {
		return owner;
	}

	double getBalance() const {
		return balance;
	}

	int  getAccountNumb() const {
		return accountNum;
	}

	void printSelf() const {
		printf("Account number: %05d\n", accountNum);
		printf("Owner: %s \n", owner.c_str());
		printf("Balance: %0.2f\n\n", balance);
	}
};

class AccountDatabase_vector {
private:
	string DBname = "";
public:
	vector<BankAccount> accountDB;
	AccountDatabase_vector(){}
	AccountDatabase_vector(const string& name_val) { DBname = name_val; }
	~AccountDatabase_vector() {
		printf("Database emptied.\n\n");
	}

	// Methods
	void createAccountToDB(const string& owner_val, double balance_val) {
		BankAccount account(owner_val, balance_val, (accountDB.size() + 1));
		accountDB.push_back(account);
	}

	void addAccountToDB(const BankAccount& account) {
		accountDB.push_back(account);
	}

	auto search(const BankAccount& account) const {
		int targetAccountNum = account.getAccountNumb();
		auto it = accountDB.begin();
		for (it; it != accountDB.end(); it++) {
			if (targetAccountNum == it->getAccountNumb()) {
				printf("Matching account found: %05d\n", it->getAccountNumb());
				printf("Owner: %s \n", it->getOwner().c_str());
				printf("Balance: %0.2f\n\n", it->getBalance());
				return it;
			}
		}
		printf("\n\n");
		return it;
	}

	void test_loop1_vector() {
		//printf("\n");
		//printf("*******************\n");
		//printf("*** Test loop 1 ***\n");
		//printf("*******************\n\n");
		for (size_t i = 0; i < accountDB.size(); i++) {
			cout << accountDB.at(i).getAccountNumb() << "\n";
			printf("Account number: %05d \n", accountDB.at(i).getAccountNumb());

		}
	}

	void test_loop2_vector() {
		//printf("\n");
		//printf("*******************\n");
		//printf("*** Test loop 2 ***\n");
		//printf("*******************\n\n");
		for (auto & account : accountDB) {
			printf("Account number: %05d \n", account.getAccountNumb());
		}
	}

	void test_emplace(const BankAccount & toBeInserted, const BankAccount & insertAt) {

		//printf("\n");
		//printf("*******************\n");
		//printf("** Test Emplace ***\n");
		//printf("*******************\n\n");
		//int targetAccountNum = insertAt.getAccountNumb();
		//for (auto it = accountDB.begin(); it != accountDB.end(); it++) {
		//	if (targetAccountNum == it->getAccountNumb()) {
		//		printf("Matching account found: %05d\n", it->getAccountNumb());
		//		printf("Owner: %s \n", it->getOwner().c_str());
		//		printf("Balance: %0.2f\n\n", it->getBalance());
		//		
		//		accountDB.emplace(it, toBeInserted);
		//		return;
		//	}
		//}
		
		// To show the original list
		test_loop2_vector();

		auto it = search(insertAt);
		if (it != accountDB.end()) {
			accountDB.emplace(it, toBeInserted);
			test_loop2_vector();
		}
		else
		{
			cout << "Account not found. \n";
		}

	}

	void test_pushAndPop(const BankAccount & toBePushed) {
		printf("\n");
		printf("*******************\n");
		printf("*** Push & Pop ****\n");
		printf("*******************\n\n");

		test_loop2_vector();

		accountDB.push_back(toBePushed);
		cout << "Accoun pushed. \n";
		test_loop2_vector();

		accountDB.pop_back();
		cout << "Account popped. \n";
		test_loop2_vector();
	}

	void summary() const {
		//cout << "\n"
		//	<< "*******************\n"
		//	<< "*** DB Summary ***\n"
		//	<< "*******************\n\n"
		//	<< "DB name: " << DBname << endl
		//	<< "Total number of accounts: " << accountDB.size() << endl;

		printf("\n");
		printf("*******************\n");
		printf("*** DB Summary ****\n");
		printf("*******************\n\n");
		printf("DB name: %s \n", DBname.c_str());
		printf("Total number of accounts: %zu \n", accountDB.size());
		printf("Account numbers: \n");
		for (auto & account : accountDB) {
			printf("%05d \n", account.getAccountNumb());
		}

		cout << "\n\n";
	}

	bool ifContains(const BankAccount& account) const {

		auto it = search(account);
		if (it == accountDB.end())
			return false;
		return true;
	}

	size_t size() const {
		return accountDB.size();
	}

	void deleteAll() {
		printf("\n");
		printf("*******************\n");
		printf("*** Delete All ****\n");
		printf("*******************\n\n");
		accountDB.clear();
	}


};

//class AccountDatabase_vectorPointers {
//private:
//	string DBname = "";
//public:
//	vector<BankAccount*> accountDB;
//	AccountDatabase_vectorPointers() {}
//	AccountDatabase_vectorPointers(const string& name_val) { DBname = name_val; }
//	~AccountDatabase_vectorPointers() {
//		cout << "Database emptied.\n\n";
//	}
//
//	// Methods
//	void createAccountToDB(const string& owner_val, double balance_val) {
//		BankAccount* account = new BankAccount (owner_val, balance_val, (accountDB.size() + 1));
//		accountDB.push_back(account);
//	}
//
//	void addAccountToDB(BankAccount* account) {
//		accountDB.push_back(account);
//	}
//
//	auto search(BankAccount* account) const {
//		int targetAccountNum = account->getAccountNumb();
//		auto it = accountDB.begin();
//		for (it; it != accountDB.end(); it++) {
//			if (targetAccountNum == (*it)->getAccountNumb()) {
//				printf("Matching account found: %05d\n", (*it)->getAccountNumb());
//				printf("Owner: %s \n", (*it)->getOwner().c_str());
//				printf("Balance: %0.2f\n\n", (*it)->getBalance());
//				return it;
//			}
//		}
//		printf("\n\n");
//		return it;
//	}
//
//	void test_loop1_vector() {
//		cout << "\n"
//			<< "*******************\n"
//			<< "*** Test loop 1 ***\n"
//			<< "*******************\n\n";
//		for (size_t i = 0; i < accountDB.size(); i++) {
//			printf("Matching account found: %05d\n", accountDB.at(i)->getAccountNumb());
//
//		}
//	}
//
//	void test_loop2_vector() {
//		cout << "\n"
//			<< "*******************\n"
//			<< "*** Test loop 2 ***\n"
//			<< "*******************\n\n";
//		for (auto & account : accountDB) {
//			printf("Matching account found: %05d\n", account->getAccountNumb());
//		}
//	}
//
//	void test_emplace( BankAccount * toBeInserted, BankAccount * insertAt) {
//		// To show the original list
//		test_loop2_vector();
//
//		cout << "\n"
//			<< "*******************\n"
//			<< "** Test emplace ***\n"
//			<< "*******************\n\n";
//		auto it = search(insertAt);
//		if (it != accountDB.end()) {
//			accountDB.emplace(it, toBeInserted);
//			test_loop2_vector();
//		}
//		else
//		{
//			cout << "Account not found. \n";
//		}
//
//	}
//
//	void test_pushAndPop(BankAccount * toBePushed) {
//		cout << "\n"
//			<< "*******************\n"
//			<< "** Test emplace ***\n"
//			<< "*******************\n\n";
//
//		test_loop2_vector();
//
//		accountDB.push_back(toBePushed);
//		cout << "Accoun pushed. \n";
//		test_loop1_vector();
//
//		accountDB.pop_back();
//		cout << "Alccount popped. \n";
//		test_loop2_vector();
//	}
//
//	void summary() const {
//		cout << "\n"
//			<< "*******************\n"
//			<< "*** DB Summary ***\n"
//			<< "*******************\n\n"
//			<< "DB name: " << DBname << endl
//			<< "Total number of accounts: " << accountDB.size() << endl;
//
//		for (auto & account : accountDB) {
//			printf("Matching account found: %05d\n", account->getAccountNumb());;
//		}
//
//		cout << "\n\n";
//	}
//
//	bool ifContains(BankAccount* account) const {
//
//		auto it = search(account);
//		if (it == accountDB.end())
//			return false;
//		return true;
//	}
//
//	size_t size() const {
//		return accountDB.size();
//	}
//
//	void deleteAll() {
//		cout << "\n"
//			<< "*******************\n"
//			<< "** Test emplace ***\n"
//			<< "*******************\n\n";
//		accountDB.clear();
//	}
//
//
//};

void printVector(const std::vector<int> & vec_val) {
	cout << "Vector values: \n";

	//Looping method 1
	for (size_t i=0; i < vec_val.size(); i++) {
		cout << vec_val.at(i) << " ";
	}

	////Looping Mehtod 2
	//for (auto num : vec_val) {
	//	cout << num << " ";
	//}

	cout << endl << endl;
}

void demoforVector() {
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

void demoforVectorOfObjects() {
	vector<string> names{ "A", "B", "C" };
	double balances[]{ 100,200,300 };

	vector<string> names2{ "AA", "BB", "CC" };
	double balances2[]{ 111,222,333 };

	AccountDatabase_vector accounts("Database1");

	for (size_t i = 0; i < (names.size()); i++) {
		accounts.createAccountToDB(names[i], balances[i]);
	}
	for (size_t i = 0; i < names.size(); i++) {
		BankAccount account(names2[i], balances2[i], accounts.size() + 1);
		accounts.addAccountToDB(account);
	}

	// Summary
	accounts.summary();

	// if Contains
	printf("\n");
	printf("*******************\n");
	printf("** Finding Match **\n");
	printf("*******************\n\n");
	BankAccount account(names2[2], balances2[2], 2);
	accounts.ifContains(account);

	// Emplace
	printf("\n");
	printf("*******************\n");
	printf("***** Emplace *****\n");
	printf("*******************\n\n");
	BankAccount toBeInserted{ "Emplaced", 999999, 99999 };
	accounts.test_emplace(toBeInserted, account);

	//// Push and pop
	//BankAccount toBePushed{ "Pushed", 66666666,66666 };
	//accounts.test_pushAndPop(toBePushed);

	//// Delete all
	//accounts.deleteAll();
}

//void demoforVectorOfPointers() {
//	string names[]{ "A", "B", "C" };
//	double balances[]{ 100,200,300 };
//
//	string names2[]{ "AA", "BB", "CC" };
//	double balances2[]{ 111,222,333 };
//
//	AccountDatabase_vectorPointers accounts("Database1");
//	for (int i = 0; i < names->size(); i++) {
//		accounts.createAccountToDB(names[i], balances[i]);
//	}
//
//	for (int i = 0; i < names->size(); i++) {
//		BankAccount * account = new BankAccount(names2[i], balances2[i], accounts.size() + 1);
//		accounts.addAccountToDB(account);
//	}
//
//	// Summary
//	accounts.summary();
//
//
//	// if Contains
//	BankAccount* account = new BankAccount(names2[2], balances2[2], 2);
//	accounts.ifContains(account);
//
//
//	// Emplace
//	BankAccount* toBeInserted = new BankAccount( "Emplaced", 999999, 99999 );
//	accounts.test_emplace(toBeInserted, account);
//
//	// Push and pop
//	BankAccount* toBePushed = new BankAccount( "Pushed", 66666666,66666 );
//	accounts.test_pushAndPop(toBePushed);
//
//	// Delete all
//	accounts.deleteAll();
//}

int main()
{
	//demoforVector();
	demoforVectorOfObjects();
	//demoforVectorOfPointers();
    return 0;
}

