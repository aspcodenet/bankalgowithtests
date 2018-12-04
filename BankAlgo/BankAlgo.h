#pragma once
#include <string>
#include <vector>
#include <map>

class Account
{
public:
	Account(std::string id, float balance = 0);
	std::string GetId();
	float GetBalance();
	void SetBalance(float balance);
private:
	std::string id;
	float balance;
};

class IAccountStorage
{
public:
	virtual void AddAccount(std::string id) = 0;
	virtual Account *GetAccount(std::string id) = 0;
};


class VectorAccountStorage : public IAccountStorage
{
public:
	~VectorAccountStorage();
	void AddAccount(std::string id) override;
	Account *GetAccount(std::string id) override;
private:
	std::vector<Account *> accounts;
};


class Bank
{
public:
	typedef enum
	{
		TRANSFER_RESULT_OK,
		TRANSFER_RESULT_INSUFFICIENT_FUNDS,
		TRANSFER_RESULT_INVALID_ACCOUNT
	} TRANSFER_RESULT;

	Bank(IAccountStorage *storage);
	bool AddAccount(std::string id);
	Account *GetAccount(std::string id);

	void Deposit(std::string kontonummerTo, float belopp);
	TRANSFER_RESULT Transfer(std::string kontonummerFrom, std::string kontonummerTo, float belopp);
private:
	IAccountStorage * accountStorage;
};

class MapAccountStorage : public IAccountStorage
{
public:
	~MapAccountStorage();
	void AddAccount(std::string id) override;
	Account *GetAccount(std::string id) override;
private:
	std::map<std::string, Account *> accounts;
};

class DistributedVectorAccountStorage : public IAccountStorage
{
public:
	~DistributedVectorAccountStorage();
	void AddAccount(std::string id) override;
	Account *GetAccount(std::string id) override;
private:
	std::vector<Account *> accountsStartingAt1;
	std::vector<Account *> accountsStartingAt2;
	std::vector<Account *> accountsStartingAt3;
	std::vector<Account *> accountsStartingAt4;
	std::vector<Account *> accountsStartingAt5;
	std::vector<Account *> accountsStartingAt6;
	std::vector<Account *> accountsStartingAt7;
	std::vector<Account *> accountsStartingAt8;
	std::vector<Account *> accountsStartingAt9;
};

