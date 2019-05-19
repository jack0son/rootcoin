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
	assert(activeAccount());

	Transaction tx(address.c_str(), to, amount);
	return tx;
}

Signature Wallet::signTransaction(Transaction tx) {
	assert(activeAccount());
	// public: Signature sign(Uint256 privateKey 
	return tx.sign(currentAcc->PrivateKey->get());
}

void Wallet::publishTransaction(Transaction tx) {
	// 1. Sign transaction
	// 2. Verify validitiy with node
	// 3. Publish to node
	// 4. Node publishes transaction
}

int Wallet::getBalance(CurvePoint publicKey) {
	// 1. 

}

void Wallet::addAccount(Account& account) {
	// 1. Generate random private key
	// 2. Create account object
	accounts.push(accounts);
	if(accounts.size() == 1) 
		currentAccount = accounts.begin();
}

bool Wallet::activeAccount() {
	if(currentAcc == accountList.end()) {
		return false;
	}

	return true;
}

Account Wallet::createAccount() {
	// 1. Generate random private key
	// 2. Create account object

}

bool Wallet::isValidAddress(string address) {
	bool valid = true;
	// KEY_SIZE in bytes, 2 chars per byte, plus 1 header byte
	if(address.size() != ADDRESS_SIZE) {
		valid = false;
	}
	return valid;
}

const size_t Wallet::KEY_SIZE = Uint256::NUM_WORDS * 8;
const size_t Wallet::ADDRESS_SIZE = (Wallet::KEY_SIZE + 1) * 2; 

Account::Account(string privKey) {
	priv = PrivateKey(privKey.c_str());
	pub = PublicKey(CurvePoint::privateExponentToPublicPoint(priv.get()));
}

Account::Account(Uint256 privKey) :
	PrivateKey(privKey),
	PublicKey(CurvePoint::privateExponentToPublicPoint(privKey))
{}
