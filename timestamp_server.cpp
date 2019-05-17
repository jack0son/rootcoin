// transaction.cpp

using std::uint8_t;

class Transaction {
	
	/*--- Fields ---*/
	punlic: PublicKey from;
	public: PublicKey to;
	public: int amount;

	public: vector<uint8_t> serialize();  
	public: 
};


