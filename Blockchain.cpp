#include "Blockchain.hpp"

using Utils::appendBytes;
using Utils::appendBytesArr;

Block::Block() 
	: myHash(NULL_HASH), prevHash(NULL_HASH) {}

Block::Block(vector<Transaction> txs, Uint256 a_nonce, Uint256 a_soln) 
	: myHash(NULL_HASH), prevHash(NULL_HASH), txList(txs), nonce(a_nonce), soln(a_soln) {}

void Block::addTransaction(Transaction &tx) {
	if(txList.size() < MAX_TX) {
		txList.push_back(tx);
	}
}

// Calculate the SHA-256 hash of the serialized block data.
// Result stored in myHash member
Sha256Hash Block::calcHash() {
	// 1. Serialize block data
	Bytes block;
	
	// Header
	appendBytesArr(block, prevHash.value, Sha256Hash::HASH_LEN);
	appendBytes(block, Utils::Uint256Bytes(nonce));
	appendBytes(block, Utils::Uint256Bytes(soln));

	// Transactions
	appendBytes(block, reward.serialize());
	for(const auto &tx : txList) {
		appendBytes(block, tx.serialize());
	}

	// 2. Compute hash
	Sha256 blkHasher;
	blkHasher.append(&block[0], block.size());
	myHash = blkHasher.getHash();

	return myHash;
}

Sha256Hash Block::getHash() const {
	return myHash;
}

Sha256Hash Block::getPrevHash() const {
	return prevHash;
}

void Block::setHash(Sha256Hash previousBlockHash) {
	prevHash = previousBlockHash;
	calcHash();
}

//____________________________________________________________________
//
Blockchain::Blockchain() 
	{}

Blockchain::Blockchain(vector<Block> blockList) 
	: blocks(blockList) {}

bool Blockchain::addBlock(Block &block) {
	// 1. Add link to chain
	block.setHash(getTop()->getHash());

	// 2. Validate block
	if(isValidBlock(block)) {
		blocks.push_back(block);
	} else {
		return false;
	}

	return true;
}

bool Blockchain::isValidBlock(const Block &block) const {
	// Block Size
	if(block.txList.size() > Block::MAX_TX) {
		return false;
	}

	// 1. Verify transactions
	for(const auto &tx : block.txList) {
		// Verify signature
		if(!tx.verify(*tx.signature)) {
			return false;
		}

		// Verify balance
		if(tx.amount <= getAddressBalance(tx.fromKey)) {
			return false;
		}

		// @missing isValidAddress(tx.from );
	}

	// @missing validate proof of work
	
	return true;
}

bool Blockchain::getAddressBalance(const PublicKey &address) const {
	int deb = 0; 
	int cred = 0; 

	// 1. Add all sends
	for(const auto &block : blocks) {
		for(const auto &tx : block.txList) {
			if(tx.fromKey == address) {
				deb += tx.amount;
			}

			if(tx.toKey == address) {
				cred += tx.amount;
			}
		}
	}

	return cred - deb;
}

//#include<unordered_map>	
// Validate that each block correctly links to the previous.
// @param sigs:		verify signature of each transaction
int Blockchain::checkChainIntegrity(bool sigs) const { 
	//std::unordered_map<PublicKey, int> balances;

	bool valid = true;
	vector<Block>::const_iterator prev;
	vector<Block>::const_iterator it;

	// @fix check first block
	for(it = blocks.begin(); it != blocks.end(); prev = it, ++it) {
		// Validate block header
		if(it->getPrevHash() != prev->getHash()) {
			valid = false;
		}

		/*if(it->myHash != it->getHash()) {
			valid = false;
		}*/

		// Validate block
		// Check that all transactions are valid
		// - this would only every be useful if downloading the blockchain
		// validate_block();
		if(sigs) {
			;;
		}
	}

}

const vector<Block>::const_iterator Blockchain::getTop() const {
	vector<Block>::const_iterator last = blocks.end();
	--last;
	return last;
}
