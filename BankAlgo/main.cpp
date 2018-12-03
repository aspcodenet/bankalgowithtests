#include "BankAlgo.h"
#include <cstdlib>
#include <iostream>
#include <chrono>


void demo()
{
	std::map<char, std::string> lookup_table;
	lookup_table['a'] = "alpha";
	lookup_table['o'] = "omega";
	lookup_table['g'] = "gamma";

	std::cout << lookup_table['g'] << std::endl;
	lookup_table.erase('g');
	if (lookup_table.count('g') > 0)
	{
		std::cout << "exists";
	}
	std::cout << lookup_table.count('g')  << std::endl;
	//prints gamma 
}

int main()
{
	demo();
	std::chrono::high_resolution_clock::time_point t1;
	std::chrono::high_resolution_clock::time_point t2;

	//VectorAccountStorage *storage = new VectorAccountStorage();
	//MapAccountStorage *storage = new MapAccountStorage();
	DistributedVectorAccountStorage *storage = new DistributedVectorAccountStorage();
	Bank *bank = new Bank(storage);

	for(int i = 0; i < 100000; i++)
		bank->AddAccount(std::to_string(i));

	std::string kontonummer;
	while (1)
	{
		std::cout << "Ange kontonummer:>" ;
		std::cin >> kontonummer;
		t1 = std::chrono::high_resolution_clock::now();
		Account *acc = bank->GetAccount(kontonummer);
		t2 = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
		std::cout << "Konto hittades ";
		if (acc == nullptr) std::cout << " inte ";
		std::cout << ". Tog " << duration << " millisekunder " << std::endl;
	}

	return 0;
}