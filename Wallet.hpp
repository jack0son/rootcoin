// Wallet API
//
// The Wallet is the User's interface to the blockchain.
//
// Implements all the basic features that would be expected of a wallet client. 
//		-
//
//// //// //// //// //// //// //// //// //// //// //// //// //// ////

/*
 * Essentially, a hardened child key is is computed with hash(parent private key + index) 
 * whereas a non-hardened child key is computed with hash(parent public key + index).
 */


// Wallet Implementation should:
// -- use memory safe containers for function arguments (e.g. strings, vectors)

#include<vector>
#include<memory>
#include<string>

// Cryptolib components
#include "Uint256.hpp";

// RootCoin lib
#include "Transaction.hpp";

using std::vector;
using std::string;

struct Account {
	PrivateKey priv;
	PublicKey pub;

	Account(string privKey);
	Account(Uint256 privKey);
}

class Wallet {

	Wallet();
	Wallet(vector<Account> *accountList);

	/*--- Fields ---*/
	public: Node *node;
	public: vector<Account>::iterator currentAcc; // what is the value of a null iterator

	/*--- Instance Members ---*/
	private: vector<Account> accounts; 
	private: Uint256 nonce;


	/*--- Instance Methods ---*/ 
	/* Transactions */
	void createTransaction(PublicKey toKey, int amount);
	void createTransaction(string toAddress, int amount);
	void signTransaction(Transaction tx);
	void publishTransaction(Transaction tx);

	/* Account Management */
	void addAccount(Account &account);
	void createAccount();
	int getBalance(CurvePoint publicKey);
	void switchAccount();
	bool activeAccount();

	/* --- Helper Methods ---*/
	static bool isValidAddress(string address);

	static const size_t KEY_SIZE;
	static const size_t ADDRESS_SIZE;

};

struct Account {
	PrivateKey privateKey;
	PublicKey publicKey;
	int balance;

	Uint256 getAddress();

};

struct PrivateKey {
	Uint256 value;
	// Other representations
};

struct PublicKey {
	CurvePoint curvePoint;
	// Other representations
}
