// MapDemo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <map>
#include <string>
#include <iostream>
#include <list>
using std::map;
using std::string;
using std::list;
using std::cout;
using std::endl;

class BankAccount {
private:
	string owner;
	int accountNum;
	double balance;

public:
	BankAccount() {}
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

class MapOfObjects {
private:
	map<int, BankAccount> accountMap;

public:
	MapOfObjects() {}
	MapOfObjects(const BankAccount & account) {
		accountMap.insert({ account.getAccountNumb(),account });
	}
	~MapOfObjects() {
		printf("Destructor exicuted.");
	}

	// Mehtods
	void printOwners() const {
		auto it = accountMap.begin();
		for (it; it != accountMap.end(); it++) {
			cout << (*it).second.getOwner() << " \n";
		}
	}

	void insertAccount(const BankAccount & account) {
		accountMap.insert({account.getAccountNumb(),account});
	}

	void addAccount(const string& owner_val, double balance_val) {
		BankAccount account(owner_val, balance_val, (accountMap.size() + 1));
		accountMap.insert({ account.getAccountNumb(),account });
	}

	void set(int accountNum, const BankAccount & account) {
		accountMap[accountNum] = account;	
	}

	size_t size() const {
		return accountMap.size();
	}

	void printAccounts() const {
		for (auto & pair : accountMap) {
			cout << " " << pair.first << ", owner " << pair.second.getOwner() << " " << "\n";
		}
	}

	void deleteAccount(int accountNum) {
		accountMap.erase(accountNum);
	}

	void deleteAll() {
		accountMap.clear();
	}
};

void printMap(map<string, int> m) {
	for (auto & pair : m) {
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

	price.erase("Banana");
	printMap(price);

	cout << "\nClearing...\n";
	price.clear();
}

void demoForMapOfObjects() {
	string names[] { "A", "B", "C"};
	double balances[]{ 100,200,300 };

	string  names2[] { "AA", "BB", "CC" };
	double balances2[]{ 111,222,333 };

	MapOfObjects m;

	for (size_t i = 0; i < 3; i++) {
		m.addAccount(names[i], balances[i]);
	}
	for (size_t i = 0; i < 3; i++) {
		BankAccount account(names2[i], balances2[i], m.size() + 1);
		m.insertAccount(account);
	}

	printf("********************\n");
	printf("* Initializing map *\n");
	printf("********************\n");
	m.printAccounts();

	printf("*********************\n");
	printf("* Delete An Account *\n");
	printf("*********************\n");
	m.deleteAccount(1);
	m.printAccounts();

	printf("*********************\n");
	printf("* Delete An Account *\n");
	printf("*********************\n");
	BankAccount account("99999", 99999, 99999);
	BankAccount account2("66666", 66666, 1);
	m.set(99999, account);
	m.set(1, account2);
	m.printAccounts();

	printf("**************\n");
	printf("* Delete All *\n");
	printf("**************\n");
	m.deleteAll();
}

int main()
{
	//demoForMap();
	demoForMapOfObjects();
    return 0;
}

