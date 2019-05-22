// Blockchain.hpp

#include "Transaction.hpp"
#include "Utils.hpp"

// Cryptolib
#include "Uint256.hpp"
#include "Sha256.hpp"
#include "CurvePoint.hpp" // should not be needed here - fix  GAIA

#include <vector>

using std::vector;

const vector<uint8_t> BZ32(Sha256Hash::HASH_LEN, 0);
const static Sha256Hash NULL_HASH = Sha256Hash(&BZ32[0], BZ32.size());

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

	
	/* --- Constructors --- */
	Block();
	Block(const vector<Transaction> txs, Uint256 a_nonce, Uint256 a_soln);

	void addTransaction(Transaction &tx);
	Sha256Hash calcHash();
	void setHash(Sha256Hash previousBlockHash);

	Sha256Hash getHash() const;
	Sha256Hash getPrevHash() const;

	// --- Static Constants
	static const size_t MAX_TX = 10;
};

class Blockchain {
	/* --- Members --- */
	vector<Block> blocks;


	/* --- Constructors --- */
	public: Blockchain();
	public: Blockchain(vector<Block> blockList);

	/* --- Public instance methods --- */
	bool addBlock(Block &block);
	bool isValidBlock(const Block &block) const;
	bool chainIsEmpty();
	int checkChainIntegrity(bool sigs) const;

	void genesis(const PublicKey &whale, const int supply = TOTAL_SUPPLY);

	// Blockchain State Accessors
	bool getAddressBalance(const PublicKey &address) const;

	private: const vector<Block>::const_iterator getTop() const;

	/* --- Helper methods --- */

	static const int TOTAL_SUPPLY = 10000;
	static const PrivateKey GAIA_PRIV;
	static const PublicKey GAIA_PUB;
};
