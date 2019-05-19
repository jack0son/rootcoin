#include "Blockchain.hpp"

Block::Block() 
	: {}

Block::Block() 
	: {}


Blockchain::Blockchain() 
	: {}

Blockchain::Blockchain() 
	: {}

Blockchain::Blockchain() 
	: {}

bool Blockchain::addBlock(Block &block) {
	// 1. Validate block
	if(!validate

}

bool Blockchain::isValidBlock(Block &block) {
	// Serialize input data
	// Use crypto library to produce sha-256 hash
	
	// 1. Verify transactions
	for(Transaction tx : block.txList) {
		// Verify signature
		if(!tx.verify(*tx.signature)) {
			return false;
		}

		// Verify balance
		if(amount < getAddressBalance(tx.address)) {
			return false;
		}
	}

	// 2. Verify hash
	// @missing
	
	return true;
}

bool Blockchain::getAddressBalance(PublicKey address) {
	int balance; 
	// 1. Add all sends
	for(Block b : blocks) {

	}

	// 2. Add all receives

	return balance;
}

int Blockchain::validate() { 
	//
	bool valid = true;
	for(vector<Block>::iterator it = blockchain.begin(); it != blockchain.end(); ++it) {
		vector<Block>::iterator prev = it - 1;

		// Validate block header
		if(*it.prevHash != *prev.myHash) {
			valide = false;
		}


		// Validate block
		validate_block();
	}

}
