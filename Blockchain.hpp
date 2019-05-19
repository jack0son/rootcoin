// Blockchain.hpp

#include "Transaction.hpp"

// Cryptolib
#include "Uint256.hpp"
#include "Sha256Hash.hpp"

class Block {

	// Block header
	Sha256Hash myHash;
	Sha256Hash prevHash;
	Uint256 nonce;
	Uint256 timestamp;

	// Transaction list
	Transaction reward;	// Block reward
	vector<Transaction> txList;

	
	// --- Constructors ---
	Block();
	Block(vector<Transactions> txs, Block prevBlock, Uint256 nonce);


	void addTransaction(Transaction tx);
	void hash();

}

class Blockchain {
	/* --- Members --- */
	vector<Block> blocks;


	/* --- Constructors --- */
	Blockchain();
	Blockchain(vector<blocks>)

	/* --- Public instance methods --- */
	bool addBlock(Block block);
	bool isValidBlock(Block block);
	int validate();


	/* --- Helper methods --- */

};

struct BalanceCache {
};
