// RootCoin lib
#include "Wallet.hpp"

Node::Node(Node&& other) 
	: dummy(0)
{
	dummy = other.dummy;
}
Node::Node() : dummy(0) {}

Wallet::Wallet(vector<Account> &accountList) 
	: accounts(accountList), node() {}


Wallet::Wallet() 
	: node() {}

Transaction Wallet::createTransaction(PublicKey to, int amount) {
	Transaction tx(currentAcc->pub, to, amount);
	signTransaction(tx);
	return tx;
}

Transaction Wallet::createTransaction(string toAddress, int amount) {
	assert(isValidAddress(toAddress));
	assert(hasAccount());

	Transaction tx(
		currentAcc->pub.toString().c_str(),
		toAddress.c_str(),
		amount
	);

	signTransaction(tx);
	return tx;
}

Signature Wallet::signTransaction(Transaction &tx) {
	assert(hasAccount());
	// public: Signature sign(Uint256 privateKey 
	return tx.sign(currentAcc->priv.get());
}

void Wallet::publishTransaction(Transaction tx) {
	// 1. Sign transaction
	// 2. Verify validitiy with node
	// 3. Publish to node
	// 4. Node publishes transaction
}

int Wallet::getBalance(const PublicKey &publicKey) {
	// 1. node.getBalance();

}

void Wallet::addAccount(Account account) {
	// 1. Generate random private key
	// 2. Create account object
	accounts.push_back(account);
	if(accounts.size() == 1) 
		currentAcc = accounts.begin();
}

void Wallet::addAccount(string privKey) {
	// 1. Generate random private key
	// 2. Create account object
	Account account(privKey);
	accounts.push_back(account);
	if(accounts.size() == 1) 
		currentAcc = accounts.begin();
}

bool Wallet::hasAccount() const{
	if(currentAcc == accounts.end()) {
		return false;
	}

	return true;
}

Account Wallet::createAccount() {
	// 1. Generate random private key
	// 2. Create account object

}

bool Wallet::isValidAddress(string address) {
	// @fix this logic should sit within public key class
	bool valid = true;
	// KEY_SIZE in bytes, 2 chars per byte, plus 1 header byte
	if(address.size() != Transaction::ADDRESS_SIZE) {
		valid = false;
	}
	return valid;
}


Account::Account(string privKey)
	:	priv(privKey.c_str()),
		pub(CurvePoint::privateExponentToPublicPoint(priv.get()))
{}

Account::Account(Uint256 privKey)
	:	priv(privKey), 
		pub(CurvePoint::privateExponentToPublicPoint(privKey))
{}
