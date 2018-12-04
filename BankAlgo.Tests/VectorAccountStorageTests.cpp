#include "pch.h"
#include "../BankAlgo/BankAlgo.h"

TEST(VectorAccountStorageTests, WhenAddingAccountItShouldBePossibleToFetch) {
	VectorAccountStorage storage;
	storage.AddAccount("123");

	Account *acc = storage.GetAccount("123");
	EXPECT_EQ("123", acc->GetId());
}

TEST(VectorAccountStorageTests, NonExistingShouldGiveNull) {
	VectorAccountStorage storage;
	storage.AddAccount("123");

	Account *acc = storage.GetAccount("1231");
	EXPECT_EQ(nullptr, acc);
}


TEST(VectorAccountStorageTests, AccountsWithIdLengthGreaterThan10ShouldNotBeStored) {
	VectorAccountStorage storage;
	try
	{
		storage.AddAccount("12345678901");
	}
	catch (...)
	{

	}

	Account *acc = storage.GetAccount("12345678901");
	EXPECT_EQ(nullptr, acc);
}

TEST(VectorAccountStorageTests, AccountsWithIdLengthGreaterThan10ShouldThrowException) {
	VectorAccountStorage storage;

	EXPECT_THROW(storage.AddAccount("12345678901"), std::length_error);
}


TEST(VectorAccountStorageTests, AccountsWithIdLengthLessThan11ShouldBeStored) {
	VectorAccountStorage storage;
	storage.AddAccount("1234567890");

	Account *acc = storage.GetAccount("1234567890");
	EXPECT_EQ("1234567890", acc->GetId());
}


TEST(VectorAccountStorageTests, AccountsWithIdLength8ShouldBeStored) {
	VectorAccountStorage storage;
	storage.AddAccount("12345678");

	Account *acc = storage.GetAccount("12345678");
	EXPECT_EQ("12345678", acc->GetId());
}