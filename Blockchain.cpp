#include "Blockchain.hpp"

using Utils::appendBytes;
using Utils::appendBytesArr;

Block::Block() 
	: myHash(NULL_HASH), prevHash(NULL_HASH) {}

Block::Block(const vector<Transaction> txs, Uint256 a_nonce, Uint256 a_soln) 
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
	appendBytes(block, Utils::Uint256ToBytes(nonce));
	appendBytes(block, Utils::Uint256ToBytes(soln));

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

	const char GAIA_PRIV_STR[65] = "0000000000000000000000000000000000000000000000000000000000000002";
	const char GAIA_PUB_STR[129] = "c6047f9441ed7d6d3045406e95c07cd85c778e4b8cef3ca7abac09b95c709ee51ae168fea63dc339a3c58419466ceaeef7f632653266d0e1236431a950cfe52a";
Blockchain::Blockchain() 
	: GAIA_PRIV(GAIA_PRIV_STR), GAIA_PUB(GAIA_PUB_STR) {}

Blockchain::Blockchain(vector<Block> blockList) 
	: GAIA_PRIV(GAIA_PRIV_STR), GAIA_PUB(GAIA_PUB_STR), blocks(blockList) {}

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



//#include<unordered_map>	
// Validate that each block correctly links to the previous.
// @param sigs:		verify signature of each transaction
int Blockchain::checkChainIntegrity(bool sigs) const { 
	//std::unordered_map<PublicKey, int> balances;
	vector<Block>::const_iterator it, prev;

	// @fix check first block
	for(it = blocks.begin(); it != blocks.end(); prev = it, ++it) {
		// Validate block header
		if(it->getPrevHash() != prev->getHash()) {
			return false;
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
	return true;
}


Block Blockchain::getBlock(size_t depth) const {
	assert(depth < blocks.size());
	return blocks[depth];
}
#include <iostream>
#include <sstream>
#include <string>
#include "Utils.hpp"
std::string printTx(Transaction &tx) {

	std::stringstream ss;

	using Utils::bytesToStr;
	using std::endl;
	ss << " ~~~ Tx Details ~~~ \n";
	ss << "from:\t" << bytesToStr(tx.fromKey.toBytes());
	ss << "\nto:\t" << bytesToStr(tx.toKey.toBytes());
	ss << "\namnt:\t" << tx.amount;
	ss << "\nsig:\t" << bytesToStr(tx.signature->toBytes());
	ss << endl;
	return ss.str();
}

// @fix design should not treat genisis as a special case
void Blockchain::genesis(const PublicKey &whale, const int supply) {
	assert(chainIsEmpty());

	Transaction genTx(GAIA_PUB, whale, supply);
	std::cout << "\t\t-------------- GENESIS TX --------------\n";
	genTx.sign(GAIA_PRIV.get());
	std::cout << printTx(genTx);
	std::cout << "\t\t--------------^^^^^^^^^^^--------------\n";
	Block genesisBlock;
	genesisBlock.addTransaction(genTx);
	std::cout << "Added transaction." << std::endl;
	blocks.push_back(genesisBlock);
	std::cout << "Pushed genesis block." << std::endl;
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

bool Blockchain::chainIsEmpty() const {
	/*if(getTop() == blocks.begin()) {
		return true;
	}*/
	return getTop() == blocks.begin();
}

const vector<Block>::const_iterator Blockchain::getTop() const {
	vector<Block>::const_iterator last = blocks.end();
	if(blocks.size() > 0)
		--last;
	return last;
}

// @fix GAIA
//const PublicKey Blockchain::GAIA_PUB("79be667ef9dcbbac55a06295ce870b07029bfcdb2dce28d959f2815b16f81798483ada7726a3c4655da4fbfc0e1108a8fd17b448a68554199c47d08ffb10d4b8");
//const PrivateKey Blockchain::GAIA_PRIV("0000000000000000000000000000000000000000000000000000000000000001");
//const Uint256 dummy("FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFDBAAEDCE6AF48A03BBFD25E8CD0364141");
