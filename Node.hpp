
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
