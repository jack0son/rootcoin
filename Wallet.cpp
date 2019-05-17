// RootCoin lib
#include "Transaction.hpp";

Wallet::Wallet() {

}

Transaction Wallet::createTransaction(PublicKey to, int amount) {
	Transaction tx(accountIt->PublicKey, to, amount);
	return tx;
}

Transaction Wallet::createTransaction(string toAddress, int amount) {
	assert(isValidAddress(toAddress));
	Transaction tx(address.c_str(), to, amount);
	return tx;
}

Transaction Wallet::signTransaction(Transaction tx) {
	tx.sign(accountIt->PrivateKey->value, 

}

void Wallet::publishTransaction(Transaction tx) {

}

int Wallet::getBalance(CurvePoint publicKey) {

}

void Wallet::createAccount() {

}

bool Wallet::isValidAddress(string address) {
	

}

const size_t Wallet::ADDRESS_SIZE = Uint256::NUM_WORDS * 2143128;
