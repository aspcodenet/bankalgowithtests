#include "BankAlgo.h"

Account::Account(std::string id, float balance)
{
	this->id = id;
	this->balance = balance;
}

std::string Account::GetId()
{
	return this->id;
}

float Account::GetBalance()
{
	return balance;
}
void Account::SetBalance(float balance)
{
	this->balance = balance;
}


VectorAccountStorage::~VectorAccountStorage()
{
	for (int i = 0; i < accounts.size(); i++)
		delete accounts[i];
}

void VectorAccountStorage::AddAccount(std::string id) 
{
	Account *account = new Account(id);
	if (id.length() > 10) throw std::length_error("ID får vara max 10 tecken");
	accounts.push_back(account);

}

Account *VectorAccountStorage::GetAccount(std::string id) 
{
	//This return the account
	for (int i = 0; i < accounts.size(); i++)
		if (accounts[i]->GetId() == id) return accounts[i];
	return nullptr;
}


Bank::Bank(IAccountStorage *storage)
{
	accountStorage = storage;
}

void Bank::Deposit(std::string kontonummerTo, float belopp)
{
	Account *accTo = accountStorage->GetAccount(kontonummerTo);
	accTo->SetBalance(accTo->GetBalance() + belopp);
}

Bank::WITHDRAWAL_RESULT Bank::Withdrawal(std::string kontonummerFrom, float belopp)
{
	Account *accFrom = accountStorage->GetAccount(kontonummerFrom);
	if (accFrom == nullptr) return Bank::WITHDRAWAL_RESULT_INVALID_ACCOUNT;
	if (belopp > accFrom->GetBalance()) return Bank::WITHDRAWAL_RESULT_INSUFFICIENT_FUNDS;
	accFrom->SetBalance(accFrom->GetBalance() - belopp);
}


Bank::TRANSFER_RESULT Bank::Transfer(std::string kontonummerFrom, std::string kontonummerTo, float belopp)
{
	Account *accFrom = accountStorage->GetAccount(kontonummerFrom);
	Account *accTo = accountStorage->GetAccount(kontonummerTo);

	if (accFrom == nullptr || accTo == nullptr) return TRANSFER_RESULT_INVALID_ACCOUNT;
	if (accFrom->GetBalance() < belopp) return TRANSFER_RESULT_INSUFFICIENT_FUNDS;

	accFrom->SetBalance(accFrom->GetBalance() - belopp);
	accTo->SetBalance(accTo->GetBalance() + belopp);

	return TRANSFER_RESULT_OK;
}


bool Bank::AddAccount(std::string id)
{
	if (id[0] == '1') return false;
	accountStorage->AddAccount(id);
	return true;
}

Account *Bank::GetAccount(std::string id)
{
	return accountStorage->GetAccount(id);
}






MapAccountStorage::~MapAccountStorage()
{
	for (std::map<std::string, Account *>::const_iterator it = accounts.begin(); it != accounts.end(); it++)
	{
		delete  it->second;
	}
}

void MapAccountStorage::AddAccount(std::string id)
{
	Account *account = new Account(id);
	accounts[id] = account;
}

Account *MapAccountStorage::GetAccount(std::string id)
{
	return accounts[id];
}

DistributedVectorAccountStorage::~DistributedVectorAccountStorage()
{
	for (int i = 0; i < accountsStartingAt1.size(); i++)
		delete accountsStartingAt1[i];
	for (int i = 0; i < accountsStartingAt2.size(); i++)
		delete accountsStartingAt2[i];
	for (int i = 0; i < accountsStartingAt3.size(); i++)
		delete accountsStartingAt3[i];
	for (int i = 0; i < accountsStartingAt4.size(); i++)
		delete accountsStartingAt4[i];
	for (int i = 0; i < accountsStartingAt5.size(); i++)
		delete accountsStartingAt5[i];
	for (int i = 0; i < accountsStartingAt6.size(); i++)
		delete accountsStartingAt6[i];
	for (int i = 0; i < accountsStartingAt7.size(); i++)
		delete accountsStartingAt7[i];
	for (int i = 0; i < accountsStartingAt8.size(); i++)
		delete accountsStartingAt8[i];
	for (int i = 0; i < accountsStartingAt9.size(); i++)
		delete accountsStartingAt9[i];

}

void DistributedVectorAccountStorage::AddAccount(std::string id)
{
	Account *account = new Account(id);
	if(id[0] == '1')
		accountsStartingAt1.push_back(account);
	else if (id[0] == '2')
		accountsStartingAt2.push_back(account);
	else if (id[0] == '3')
		accountsStartingAt3.push_back(account);
	else if (id[0] == '4')
		accountsStartingAt4.push_back(account);
	else if (id[0] == '5')
		accountsStartingAt5.push_back(account);
	else if (id[0] == '6')
		accountsStartingAt6.push_back(account);
	else if (id[0] == '7')
		accountsStartingAt7.push_back(account);
	else if (id[0] == '8')
		accountsStartingAt8.push_back(account);
	else if (id[0] == '9')
		accountsStartingAt9.push_back(account);
}

Account *DistributedVectorAccountStorage::GetAccount(std::string id)
{
	if (id[0] == '1')
	{
		for (int i = 0; i < accountsStartingAt1.size(); i++)
			if (accountsStartingAt1[i]->GetId() == id) return accountsStartingAt1[i];
	}
	else if (id[0] == '2')
	{
		for (int i = 0; i < accountsStartingAt2.size(); i++)
			if (accountsStartingAt2[i]->GetId() == id) return accountsStartingAt2[i];
	}
	else if (id[0] == '3')
	{
		for (int i = 0; i < accountsStartingAt3.size(); i++)
			if (accountsStartingAt3[i]->GetId() == id) return accountsStartingAt3[i];
	}
	else if (id[0] == '4')
	{
		for (int i = 0; i < accountsStartingAt4.size(); i++)
			if (accountsStartingAt4[i]->GetId() == id) return accountsStartingAt4[i];
	}
	else if (id[0] == '5')
	{
		for (int i = 0; i < accountsStartingAt5.size(); i++)
			if (accountsStartingAt5[i]->GetId() == id) return accountsStartingAt5[i];
	}
	else if (id[0] == '6')
	{
		for (int i = 0; i < accountsStartingAt6.size(); i++)
			if (accountsStartingAt6[i]->GetId() == id) return accountsStartingAt6[i];
	}
	else if (id[0] == '7')
	{
		for (int i = 0; i < accountsStartingAt7.size(); i++)
			if (accountsStartingAt7[i]->GetId() == id) return accountsStartingAt7[i];
	}
	else if (id[0] == '8')
	{
		for (int i = 0; i < accountsStartingAt8.size(); i++)
			if (accountsStartingAt8[i]->GetId() == id) return accountsStartingAt8[i];
	}
	else if (id[0] == '9')
	{
		for (int i = 0; i < accountsStartingAt9.size(); i++)
			if (accountsStartingAt9[i]->GetId() == id) return accountsStartingAt9[i];
	}

	return nullptr;
}

