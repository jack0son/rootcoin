#include<vector>
#include<iostream>

int hash(int input) {

	return 3;
}
//
	// func publishTransaction
	// 1. Sign transaction
	// 2. Validate transaction against blockchain using node
	// 3. Publish to P2P network 
	// 4. Confirm 

// Simulate P2P without using networking protocols
class FakeP2P {

	vector<Peer> peers;
	
	int discover(int timeout);
	int add_peer(Peer peer);

	int broadcast(char* message);

}


class Consensus {


};


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



