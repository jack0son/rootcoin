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
#include "Uint256.hpp"

// RootCoin lib
#include "Transaction.hpp"

using std::vector;
using std::string;

struct Account {
	//private:
	PrivateKey priv;
	PublicKey pub;

	Account(string privKey);
	Account(Uint256 privKey);
};

struct Node {
	int dummy;

	Node();
	Node(Node&& other);
};


class Wallet {

	/* --- Constructors --- */
public:
	Wallet();
	Wallet(vector<Account> &accountList);

	/*--- Fields ---*/
public:
	Node node;
	//const Node &node;
	vector<Account>::iterator currentAcc; // what is the value of a null iterator


	/*--- Instance Members ---*/
public:
	vector<Account> accounts; 


	/*--- Instance Methods ---*/ 
	/* Transactions */
public:
	Transaction createTransaction(PublicKey toKey, int amount);
	Transaction createTransaction(string toAddress, int amount);
	Signature signTransaction(Transaction &tx);
	void publishTransaction(Transaction tx);


	/* Account Management */
	void addAccount(Account account);
	void addAccount(string privKey);
	Account createAccount();
	int getBalance(const PublicKey &publicKey);
	const PublicKey& getPublicKey() const;
	void switchAccount();
	bool hasAccount() const;


	/* --- Helper Methods ---*/
	static bool isValidAddress(string address);
};
