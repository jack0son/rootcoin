// Blockchain.hpp

#include "Transaction.hpp"
#include "Utils.hpp"

// Cryptolib
#include "Uint256.hpp"
#include "Sha256"

class Block {

	/* --- Instance Members ---*/
	// Block header
	private: Sha256Hash myHash;
	private: Sha256Hash prevHash;
	public: Uint256 nonce;
	public: Uint256 soln;  // POW Solution
	//Uint256 timestamp;

	// Transaction list
	public: Transaction reward;	// Block reward
	vector<Transaction> txList;

	
	// --- Constructors ---
	Block();
	Block(vector<Transactions> txs, Block &prevBlock, Uint256 &nonce);

	Sha256Hash getHash();
	Sha256Hash calcHash();
	void setHash(Sha256Hash previousBlockHash);
	void addTransaction(Transaction &tx);

	// ---
	
	static const size_t MAX_TX = 10;

}

class Blockchain {
	/* --- Members --- */
	vector<Block> blocks;


	/* --- Constructors --- */
	Blockchain();
	Blockchain(vector<blocks>)

	/* --- Public instance methods --- */
	bool addBlock(Block block);
	bool isValidBlock(const Block block) const;
	int checkChainIntegrity();
	

	const vector<Block>::iterator getTop() const;

	/* --- Helper methods --- */

};
