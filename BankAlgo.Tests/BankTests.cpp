#include "pch.h"
#include "../BankAlgo/BankAlgo.h"

class Calc
{
public:
	int Add(int a, int b)
	{
		return a + b;
	}
};


TEST(BankTests, WhenDepositBalanceShouldIncrease) {
	VectorAccountStorage *storage = new VectorAccountStorage();
	Bank bank(storage);
	storage->AddAccount("123");
	Account *acc = storage->GetAccount("123");
	acc->SetBalance(100);

	bank.Deposit("123",50);



	EXPECT_EQ(150, acc->GetBalance());
}


TEST(BankTests, WhenAdding1and2ItShouldReturn3) {
	Calc c;
	int r = c.Add(1,2);
	EXPECT_EQ(3, r);
}
TEST(BankTests, WhenAdding5and6ItShouldReturn11) {
	Calc c;
	int r = c.Add(5, 6);
	EXPECT_EQ(11, r);
}


TEST(BankTests, WhenTransferFromAccountBalanceShouldDecrease) {
	VectorAccountStorage *storage = new VectorAccountStorage();
	Bank bank(storage);
	storage->AddAccount("123");
	storage->AddAccount("456");
	Account *from = storage->GetAccount("123");
	from->SetBalance(100);
	Account *to = storage->GetAccount("456");
	to->SetBalance(200);

	bank.Transfer("123", "456", 50);
	EXPECT_EQ(50, from->GetBalance());
}

TEST(BankTests, WhenTransferToAccountBalanceShouldIncrease) {
	VectorAccountStorage *storage = new VectorAccountStorage();
	Bank bank(storage);
	storage->AddAccount("123");
	storage->AddAccount("456");
	Account *from = storage->GetAccount("123");
	from->SetBalance(100);
	Account *to = storage->GetAccount("456");
	to->SetBalance(200);

	bank.Transfer("123", "456", 50);


	EXPECT_EQ(250, to->GetBalance());
}


TEST(BankTests, WhenTransferInvalidFromAccountItShouldReturnInvalidAccount) {
	VectorAccountStorage *storage = new VectorAccountStorage();
	Bank bank(storage);
	storage->AddAccount("123");

	Bank::TRANSFER_RESULT res =  bank.Transfer("999", "123", 50);
	EXPECT_EQ(Bank::TRANSFER_RESULT_INVALID_ACCOUNT, res);
}

TEST(BankTests, WhenTransferMoreThanBalanceItShouldReturnInsufficientFunds) {
	VectorAccountStorage *storage = new VectorAccountStorage();
	Bank bank(storage);
	storage->AddAccount("123");
	storage->GetAccount("123")->SetBalance(100);
	storage->AddAccount("456");

	Bank::TRANSFER_RESULT res = bank.Transfer("123", "456", 150);
	EXPECT_EQ(Bank::TRANSFER_RESULT_INSUFFICIENT_FUNDS, res);
}

TEST(BankTests, WhenTransferInvalidToAccountItShouldReturnInvalidAccount) {
	VectorAccountStorage *storage = new VectorAccountStorage();
	Bank bank(storage);
	storage->AddAccount("123");

	Bank::TRANSFER_RESULT res = bank.Transfer("123", "456", 50);
	EXPECT_EQ(Bank::TRANSFER_RESULT_INVALID_ACCOUNT, res);
}


