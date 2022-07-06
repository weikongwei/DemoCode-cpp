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

	BankAccount(BankAccount && source) {
		owner = std::move(source.owner);
		accountNum = source.accountNum;
		balance = source.balance;
		printf("Account %05d moved.\n", accountNum);
	}

	~BankAccount() {
		printf("\n Destructor called for %05d.\n\n", accountNum);
	}

	// Methods
	void operator = (const BankAccount & source)
	{
		owner = source.owner;
		accountNum = source.accountNum;
		balance = source.balance;
		printf("A copy of account %05d created.\n", accountNum);
	}

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
	map<int, BankAccount> accountMap;

public:
	MapOfObjects() {}
	~MapOfObjects() {
		printf("Destructor exicuted.");
	}

	// Mehtods
	void printOwners() const {
		for (auto it = accountMap.begin(); it != accountMap.end(); it++) {
			cout << it->second.getOwner() << " \n";
		}
	}

	void printAccounts() const {
		for (auto & pair : accountMap) {
			cout << " " << pair.first << ", owner " << pair.second.getOwner() << " " << "\n";
		}
	}

	BankAccount* find(int accountNum) {
		auto it = accountMap.find(accountNum);
		if (it == accountMap.end())
			return nullptr;
		return &(it->second);
	}

	void insertAccount(const BankAccount & account) {
		accountMap.insert({account.getAccountNumb(),account});
	}

	void insertAccount(BankAccount && account) {
		accountMap.insert({ account.getAccountNumb(),std::move(account) });
	}

	void addAccount(const string& owner_val, double balance_val) {
		BankAccount account(owner_val, balance_val, (accountMap.size() + 1));
		accountMap.insert({ account.getAccountNumb(),std::move(account) });
	}

	void set(int accountNum, const BankAccount & account) {
		accountMap[accountNum] = account;	
	}

	size_t size() const {
		return accountMap.size();
	}

	void deleteAccount(int accountNum) {
		accountMap.erase(accountNum);
	}

	void deleteAll() {
		accountMap.clear();
	}
};

class MapOfPointers {
	map<int, BankAccount*> accountMap;

public:
	MapOfPointers() {}
	~MapOfPointers() {
		deleteAll();
		printf("Destructor exicuted.");
	}

	// Mehtods
	void printOwners() const {
		for (auto it = accountMap.begin(); it != accountMap.end(); it++) {
			cout << it->second->getOwner() << " \n";
		}
	}

	void printAccounts() const {
		for (auto & pair : accountMap) {
			cout << " " << pair.first << ", owner " << pair.second->getOwner() << " " << "\n";
		}
	}

	BankAccount* find(int accountNum) {
		auto it = accountMap.find(accountNum);
		if (it == accountMap.end())
			return nullptr;
		return it->second;
	}

	void insertAccount(BankAccount * account) {
		accountMap.insert({ account->getAccountNumb(),account });
	}

	void addAccount(const string& owner_val, double balance_val) {
		BankAccount* account = new BankAccount(owner_val, balance_val, (accountMap.size() + 1));
		accountMap.insert({ account->getAccountNumb(),account });
	}

	void set(int accountNum, BankAccount * account) {
		accountMap[accountNum] = account;
	}

	size_t size() const {
		return accountMap.size();
	}

	void deleteAccount(int accountNum) {
		accountMap.erase(accountNum);
	}

	void deleteAll() {
		for (auto & pair : accountMap)
			delete pair.second;
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
		m.insertAccount(std::move(account));
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

void demoForMapOfPointers() {
	string names[]{ "A", "B", "C" };
	double balances[]{ 100,200,300 };

	string  names2[]{ "AA", "BB", "CC" };
	double balances2[]{ 111,222,333 };

	MapOfPointers m;

	for (size_t i = 0; i < 3; i++) {
		m.addAccount(names[i], balances[i]);
	}
	for (size_t i = 0; i < 3; i++) {
		BankAccount* account = new BankAccount(names2[i], balances2[i], m.size() + 1);
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
	BankAccount* account = new BankAccount("99999", 99999, 99999);
	BankAccount* account2 = new BankAccount("66666", 66666, 1);
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
	//demoForMapOfObjects();
	demoForMapOfPointers();
    return 0;
}

