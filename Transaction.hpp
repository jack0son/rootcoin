// RootCoin lib
/* List of ROOTcoin primitives:
 *		- Account
 *		- Address
 *		- Public Key
 *		- Private Key
 *		- Transaction amount
 */

// Building a cryptocurrency from first principles
// ROOTCoin

// transaction.hpp
#include<vector>
#include<cstring>
#include<cassert>
#include<memory>

// Cryptolib components
#include "Uint256.hpp"
#include "Sha256.hpp"
#include "CurvePoint.hpp"
#include "FieldInt.hpp"
#include "Ecdsa.hpp"

// Rootcoin tools
#include "Utils.hpp"


using std::uint8_t;
using std::vector;
using std::unique_ptr;

typedef vector<uint8_t> Bytes;

struct Signature {
	Uint256 r; // output
	Uint256 s; //

	Signature(Uint256& r, Uint256& s);
	Signature();
	Bytes toBytes() const;
};

struct PrivateKey {
	const Uint256 value;

	PrivateKey(const Uint256 val);
	Bytes toBytes() const;
	const Uint256 get() const;
};

struct PublicKey {
	CurvePoint curvePoint;

	PublicKey(const Bytes &keyBytes); 
	PublicKey(const char* address);
	PublicKey(const CurvePoint &cp);
	Bytes toBytes() const;
};

class Transaction {
	/*--- Fields ---*/
	public:
		PublicKey fromKey;// sending address 
		PublicKey toKey;  // recipient address
		int amount;		// amount to send
		std::shared_ptr<Signature> signature; // @fix why is this a pointer

	
	/*--- Constructors ---*/
	Transaction(const Bytes &fromAddr, const Bytes &toAddr, int sendAmount);
	Transaction(const char *fromAddr, const char *toAddr, int sendAmount);
	Transaction(PublicKey &from, PublicKey &to, int sendAmount);
	Transaction();


	/*--- Public instance methods ---*/
	// Calculate ECDSA signature
	public: Signature sign(Uint256 privateKey); 
	// how to verify API isn't storing PK?
	
	// Verify transaction origin
	public: bool verify(Signature sig) const; 
	
	// Create a transaction hash (message hash for transaction contents)
	public: Sha256Hash hash() const;

	
	/*--- Helper methods ---*/
	// Serialize transaction fields (for hash calculation)
	public: vector<uint8_t> serialize() const;  
	
	public: static vector<uint8_t> serializeCurvePoint(CurvePoint curvePoint) ;
	public: static unique_ptr<CurvePoint> deserializeCurvePoint(const vector<uint8_t> bytes) ; 
	public: static unique_ptr<CurvePoint> deserializeCurvePoint(const char* curvePointStr) ;
	
	//public: static bool verify(char* from, char* to, Signature signature) ;

	/*--- Public static constants ---*/
	public: static Uint256 DEFAULT_NONCE;
};
