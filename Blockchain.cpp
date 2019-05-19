#include "Blockchain.hpp"

Block::Block() 
	: {}

Block::Block(vector<Transactions> txs, Uint256 a_nonce) 
	: txList(txs), nonce(a_nonce) {}

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
	Bytes* &block = &block
	appendBytes(&block, &header);
	appendBytesArr(&block, prevHash.value, Sha256Hash::HASH_LEN);
	appendBytes(&block, Uint256Bytes(nonce));
	appendBytes(&block, Uint256Bytes(soln));

	Bytes txBytes;
	appendBytes(&txBytes, &reward.serialize());
	for(const auto &tx : txList) {
		apppendBytes(&txBytes, &tx.serialize());
	}

	appendBytes(&block, &txBytes);

	// 2. Compute hash
	Sha256 blkHasher;
	blkHasher.append(&block, block.size());

	myHash = blkHasher.getHash();

	return myHash;
}

Sha256Hash Block::getHash() {
	return myHash;
}

void Block::setHash(Sha256Hash previousBlockHash) {
	prevHash = previousBlockHash;
	calcHash();
}

//____________________________________________________________________
//
Blockchain::Blockchain() 
	: {}

bool Blockchain::addBlock(Block &block) {
	// 1. Add link to chain
	block.setHash(getTop()->getHash());

	// 2. Validate block
	if(isValidBlock(block)) {
		blocks.push(block);
	} else {
		return false;
	}

	return true;
}

bool Blockchain::isValidBlock(const Block &block) const {
	// Serialize input data
	// Use crypto library to produce sha-256 hash
	
	// @missing validate proof of work

	// Block Size
	if(block.txList.size() > Block::MAX_TX) {
		return false;
	}

	// 1. Verify transactions
	for(const auto &tx : block.txList) {
		// Verify signature
		if(!tx.verify(tx->signature)) {
			return false;
		}

		// Verify balance
		if(amount < getAddressBalance(tx.address)) {
			return false;
		}

		// Verify 
	}

	// 2. Verify hash
	// @missing
	
	return true;
}

bool Blockchain::getAddressBalance(const PublicKey &address) {
	int deb = 0; 
	int cred = 0; 

	// 1. Add all sends
	for(const auto &block : blocks) {
		for(const auto &tx : block.txList) {
			if(tx.from == address) {
				deb += tx.amount;
			}

			if(tx.to == address) {
				cred += tx.amount;
			}
		}
	}

	return cred - deb;
}

//#include<unordered_map>	
// Validate that each block correctly links to the previous.
// @param sigs:		verify signature of each transaction
int Blockchain::checkChainIntegrity(bool sigs) { 
	//std::unordered_map<PublicKey, int> balances;

	bool valid = true;
	vector<Block>::iterator prev;
	// @fix check first block
	for(vector<Block>::iterator it = blockchain.begin(); it != blockchain.end(); prev = it, ++it) {
		// Validate block header
		if(*it.prevHash != *prev.myHash) {
			valid = false;
		}

		if(*it.myHash != *it.getHash()) {
			valid = false;
		}

		// Validate block
		// Check that all transactions are valid
		// - this would only every be useful if downloading the blockchain
		// validate_block();
		if(sigs) {
			;;
		}
	}

}

const vector<Block>::iterator Blockchain::getTop() const {
	vector<Block>::iterator last = blocks.end();
	--last;
	return last;
}
