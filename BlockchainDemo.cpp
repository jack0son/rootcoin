#include <string>

#include "Blockchain.hpp"
#include "Wallet.hpp"

using std::vector;
using std::string;

typedef vector<Transaction> Txs;

Blockchain instantiateBlockchain(Txs txList) {
	Blockchain blockchain; 

	// Genesis block

}

int main() {
	vector<string> privKeys = {
		"",
		"",
		""
	};

	Wallet wallet1;

	for(string key : privKeys) {
		wallet1.addAccount(Account(key));
	}

	return 0;
}


//Txs getDummyTxs(Wallet &wallet) {
Txs getDummyTxs() {

}

