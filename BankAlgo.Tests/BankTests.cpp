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

class bankFixture : public testing::Test {
public:
	Bank *bank;
	IAccountStorage *storage;
	bankFixture() {
		// initialization code here
	}

	void SetUp() {
		// code here will execute just before the test ensues 
		storage = new VectorAccountStorage();
		bank = new Bank(storage);
	}


	void TearDown() {
		// code here will be called just after the test completes
		// ok to through exceptions from here if need be
	}

	~bankFixture() {
		// cleanup any pending stuff, but no exceptions allowed
	}

	Account *CreateAccount(std::string kontonummer, float balance = 0)
	{
		storage->AddAccount("123");
		Account *acc = storage->GetAccount("123");
		acc->SetBalance(balance);
		return acc;
	}
	// put in any custom data members that you need 
};


TEST_F(bankFixture, WhenWithdrawalBalanceShouldDecrease) {
	Account *acc = CreateAccount("123", 100);
	bank->Withdrawal("123", 75);
	EXPECT_EQ(25, acc->GetBalance());
}

TEST_F(bankFixture, WithdrawalNotAllowedifAmountGreaterThanBalance) {
	Account *acc = CreateAccount("123", 50);
	bank->Withdrawal("123", 75);
	EXPECT_EQ(50, acc->GetBalance());
}



TEST_F(bankFixture, WhenDepositBalanceShouldIncrease) {
	Account *acc = CreateAccount("123", 100);
	bank->Deposit("123",50);
	EXPECT_EQ(150, acc->GetBalance());
}


TEST(BankTests, WhenAdding5and6ItShouldReturn11) {
	Calc c;
	int r = c.Add(5, 6);
	EXPECT_EQ(11, r);
}


TEST_F(bankFixture, WhenTransferFromAccountBalanceShouldDecrease) {
	storage->AddAccount("123");
	storage->AddAccount("456");
	Account *from = storage->GetAccount("123");
	from->SetBalance(100);
	Account *to = storage->GetAccount("456");
	to->SetBalance(200);

	bank->Transfer("123", "456", 50);
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


