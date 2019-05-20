#include <iostream>
#include <string>

#include "Blockchain.hpp"
#include "Wallet.hpp"

using std::vector;
using std::string;
using std::cout;
using std::endl;

typedef vector<Transaction> Txs;

void printTx(Transaction &tx);
void printBytes(const Bytes &bytes);
void printAcc(Account &a);

Blockchain instantiateBlockchain(Txs txList) {
	;;
}

int main() {
	vector<string> privKeys = {
		"E9873D79C6D87DC0FB6A5778633389F4453213303DA61F20BD67FC233AA33262",
		"B8EF4E4640FBBD526166FF260EB65EC2B3B60064CCE2DA9747201BA201E90F7F",
		"7A6D055110F4296A85E8122B32F87AD32A58CF9BB73435088102638D7DECE1F2"
	};

	Wallet wallet1;

	for(string key : privKeys) {
		cout << "Adding account using key: " << key << endl;
		wallet1.addAccount(Account(key));
	}
	cout << endl;

	cout << "Wallet 1 - Current account::::\n";
	printAcc(*wallet1.currentAcc);
	cout << endl;

	Wallet wallet2;
	wallet2.addAccount(Account(privKeys[1]));
	cout << "Wallet 2 - Current account::::\n";
	printAcc(*wallet2.currentAcc);
	cout << endl;

	cout << "Wallet 1 - Current account::::\n";
	printAcc(*wallet1.currentAcc);
	cout << endl;

	Wallet wallet3;
	wallet3.addAccount(Account(privKeys[2]));
	cout << "Wallet 3 - Current account::::\n";
	printAcc(*wallet3.currentAcc);
	cout << endl;

	Blockchain blockchain; 
	Transaction tx1 = wallet1.createTransaction(wallet3.currentAcc->pub, 1);
	wallet1.signTransaction(tx1);

	printTx(tx1);

	return 0;
}


//Txs getDummyTxs(Wallet &wallet) {
Txs getDummyTxs() {

}

void printBytes(const Bytes &bytes) {
	for(uint8_t b : bytes) {
		std::cout << Utils::hexify<uint8_t>(b);
	}
}

void printTx(Transaction &tx) {
	using namespace std;

	cout << " ~~~ Tx Details ~~~ \n";
	cout << "from:\t"; printBytes(tx.fromKey.toBytes());
	cout << "\nto:\t"; printBytes(tx.toKey.toBytes());
	cout << "\namnt:\t" << tx.amount;
	cout << "\nsig:\t"; printBytes(tx.signature->toBytes());
	cout << endl;

}

void printAcc(Account &a) {
	using namespace std;

	cout << " ~~~ Account Details ~~~ \n";
	cout << "priv:\t"; printBytes(a.priv.toBytes());
	cout << "\npub:\t"; printBytes(a.pub.toBytes());
	cout << endl;

}
