#include<vector>
#include<iostream>

int hash(int input) {

	return 3;
}

// Simulate P2P without using networking protocols
class FakeP2P {

	vector<Peer> peers;
	
	int discover(int timeout);
	int add_peer(Peer peer);

	int broadcast(char* message);

}

// Maintain the blockchain 
class TSServer {

	vector<Block> blockchain;

	int add_block(Block block);
	int validate_block(Block block);
	int validate_chain();

	int validate_chain() { 
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


	void validate_block(Block block);
	void add_block(Block block) {
		// Serialize input data
		// Use crypto library to produce sha-256 hash
		
	}

};

class Consensus {


};

class Node {

	vector<Transaction> txs_to_publish; 
	vector<Transaction> txs_received;


	public:
	// Each block received from another node needs to be compared to the
	// tx_received list to remove any validated transactions
	void reconcile_block(Block block);

	void publish_block(Block block);

	// Look for TXs broadcast on the network
	void receive_txs();

	void queue_tx(Transaction tx);


	// Publish queued transactions to the network
	void publish_txs() {
		// Check for conflicting transactions
		
		// Publish the first-in valid transactions to network

		// Add them to txs_received list - I want my own TXs published

	}	

}

// Track the present state of the world
// This is a cryptocurrency, so state is determined by totalling previous
// transactions
class StateMachine {

}

// Proof of work
class POW {
	int nonce; // number of zero bits


	int work(); // scan for solutions

}

class Block {

	// Block header
	int myHash;
	int prevHash;
	int nonce;
	int timestamp;

	// Transaction list
	vector<Transaction> txList;

	Block() {
		

	}

	~Block() {

	}	

	void addTransaction(Transaction tx);

};

