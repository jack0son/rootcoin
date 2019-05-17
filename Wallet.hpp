// Wallet API
//
// Implements all the basic features that would be expected of a wallet client. 
//		-
//
//// //// //// //// //// //// //// //// //// //// //// //// //// ////

#include<vector>

// Cryptolib components
#include "Uint256.hpp";

// RootCoin lib
#include "Transaction.hpp";

using std::vector;

class Wallet {

	Wallet();
	Wallet(Account *accountList);

	/*--- Fields ---*/
	public: Node *node;
	public: Account *account;

	/*--- Instance Members ---*/
	private: vector<Account> accounts; 


	/*--- Instance Methods ---*/ 
	void createTransaction({... transaction params});
	void signTransaction(Transaction tx);
	void publishTransaction(Transaction tx);

	int getBalance(CurvePoint publicKey);

	void createAccount();

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
