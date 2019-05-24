#include <iostream>
#include <cstring>

#include "Transaction.hpp"
#include "testData.cpp"
#include "Utils.hpp"

// Crypto lib
#include "Ecdsa.hpp" 
#include "Sha256.hpp"
#include "Uint256.hpp"
#include "CurvePoint.hpp"

typedef vector<uint8_t> Bytes;

void printBytes(Bytes bytes) {
	for(uint8_t b : bytes) {
		std::cout << Utils::hexify<uint8_t>(b);
	}
}

void printTx(Transaction &tx) {
	using namespace std;

	cout << " ~~~ Tx Details ~~~ \n";
	cout << "from:\t"; printBytes(tx.fromKey.toBytes());
	cout << "\nto:\t"; printBytes(tx.toKey.toBytes());
	cout << "\namnt:\t" << tx.amount;
	cout << endl;

}


void print_bn(Uint256 bn) {
	for(int i=0; i<Uint256::NUM_WORDS; i++) {
		std::cout << bn.value[i];

	}
}


int count = 0;
void testTx(SignCase c) {
	using std::cout; 
	using std::endl;

	int amount = 1;

	cout << "Case " << count << ":\n";

	PrivateKey fromPrivKey(Uint256(c.privateKey));

	// Create Account from private key
	CurvePoint fromPoint = CurvePoint::privateExponentToPublicPoint(fromPrivKey.value);
	PublicKey from(fromPoint);

	//Uint256 toPrivKey(c.msgHash);
	PrivateKey toPrivKey(Uint256(c.msgHash));
	CurvePoint toPoint = CurvePoint::privateExponentToPublicPoint(toPrivKey.value);
	PublicKey to(toPoint);

	// Transaction built from byte strings
	Bytes fromKey = Transaction::serializeCurvePoint(fromPoint);
	Bytes toKey = Transaction::serializeCurvePoint(toPoint);
	cout << "tx1:" << endl;
	Transaction tx2(fromKey, toKey, amount);
	cout << "tx2:" << endl;
	Transaction tx(from.toBytes(), to.toBytes(), amount);

	char *fromStr = new char[129];
	char *toStr = new char[129];
	
	// Transaction built from string keys
	cout << "tx3:" << endl;
	/*Transaction tx3(
		strcat(strcat(fromStr, c.privateKey), c.msgHash),
		strcat(strcat(toStr, c.expectedR), c.expectedS), 
		amount
	);*/

	// Transaction built from public key objects
	cout << "tx4:" << endl;
	Transaction tx4(from, to, amount);

	// Signing
	Signature sig2 = tx2.sign(fromPrivKey.get());

	printTx(tx);
	cout << "\nSignature:\n\t";
	printBytes(sig2.toBytes());
	cout << "\n^^^ ^^^ ^^^ ^^^ ^^^\n\n";
}

int main() {
	
	for(const SignCase &c : cases) {
		if(count++ == 1)
			continue;
		//if(count > 1)
			testTx(c);
	}


	return 0;
}
