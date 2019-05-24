#include "Transaction.hpp"

// Convention: constructors which map directly to member variables should use
// longer names to give the prototype more clarity.
Transaction::Transaction(const Bytes &fromAddr, const Bytes &toAddr, int sendAmount)
	: fromKey(fromAddr), toKey(toAddr), amount(sendAmount) {}

Transaction::Transaction(const char *fromAddr, const char *toAddr, int sendAmount)
	: fromKey(fromAddr), toKey(toAddr), amount(sendAmount) {}

Transaction::Transaction(const PublicKey &from, const PublicKey &to, int sendAmount)
	: fromKey(from), toKey(to), amount(sendAmount) {}

Transaction::Transaction() :
	fromKey(CurvePoint::ZERO), toKey(CurvePoint::ZERO), amount(0) {}

Transaction::Transaction(const Transaction& t) :
	fromKey(t.fromKey), toKey(t.toKey), amount(t.amount), 
	signature(new Signature(*t.signature)) {}

#include <iostream>
Signature Transaction::sign(Uint256 privateKey) {
//Signature Transaction::sign(Uint256 privateKey, Uint256 nonce = DEFAULT_NONCE) {
	// 1. Create the message hash
	using std::cout;
	using std::endl;
	const Sha256Hash txHash = getHash();
	std::cout << "\nTX HASH: " << Utils::toStr(txHash) << "\n";

	// msgHas
	//	- prev transaction ("amount")
	//	- to publicKey

	Uint256 r, s; // cryptolib 

	// 2. Call Ecdsa sign method
	Ecdsa::sign(privateKey, txHash, DEFAULT_NONCE, r, s);	
	cout << "r : " << Utils::toStr(r) << endl;
	cout << "s : " << Utils::toStr(s) << endl;
	
	// 3. Store and return results
	Signature sig(r, s);
	signature = unique_ptr<Signature>(new Signature(r, s));

	return sig;
}

bool Transaction::verify(Signature &sig) const {
	// 1. Create the message hash
	const Sha256Hash txHash = getHash();
	// bool Ecdsa::verify(const CurvePoint &publicKey, const Sha256Hash &msgHash, const Uint256 &r, const Uint256 &s)
	return Ecdsa::verify(fromKey.curvePoint, txHash, sig.r, sig.s); 
}

Sha256Hash Transaction::getHash() const {
	//Cryptolib expects array of uint8_t bytes
	Sha256 txHasher;
	// Appends message bytes to this ongoing hasher, and returns this object itself.
    //public: Sha256 &append(const std::uint8_t bytes[], std::size_t len);      	
	
	vector<uint8_t> txBytes = serialize();
	
	txHasher.append(&txBytes[0], txBytes.size());
	
	return txHasher.getHash();
}

vector<uint8_t> Transaction::serialize() const {
	// Specification of a rootcoint serialized transaction
	vector<uint8_t> serial;
	
	vector<uint8_t> keyBytes = toKey.toBytes();
	Utils::appendBytes(keyBytes, fromKey.toBytes()); // save extra call to toBytes();
	//Utils::appendBytes(serial, keyBytes);
	//keyBytes.insert(keyBytes.end(), fromKey.toBytes().begin(), fromKey.toBytes().end());
	serial.insert(serial.end(), keyBytes.begin(), keyBytes.end());
	serial.push_back((uint8_t) amount);
	//std::cout << "serial size: " << serial.size() << std::endl;
	//std::cout << "TX_SIZE: " << TX_SIZE() << std::endl;

	assert(serial.size() == TX_SIZE());

	return serial;
}

vector<uint8_t> Transaction::serializeCurvePoint(CurvePoint cp) {
	// Specification of a rootcoint serialized public key
	vector<uint8_t> address;

	size_t size = Uint256::NUM_WORDS * 4;
	uint8_t serial[size * 2]; 

	cp.normalize();
	cp.x.getBigEndianBytes(&serial[0]);
	cp.y.getBigEndianBytes(&serial[size]);

	address.insert(address.end(), serial, serial + (size*2));

	return address;
}


unique_ptr<CurvePoint> Transaction::deserializeCurvePoint(const vector<uint8_t> bytes) {
	// Specification of a rootcoint serialized public key
	size_t size = Uint256::NUM_WORDS * 4;
	assert(bytes.size() == size*2);
	
	Uint256 x(&bytes[0]);
	Uint256 y(&bytes[size]);

	unique_ptr<CurvePoint> cp(new CurvePoint(FieldInt(x), FieldInt(y)));

	return cp;
}

unique_ptr<CurvePoint> Transaction::deserializeCurvePoint(const char* curvePointStr) {
	// Specification of a rootcoint serialized public key
	size_t size = Uint256::NUM_WORDS * 4;
	assert(strlen(curvePointStr) == size*4);
	
	char* xStr = new char[size*2]; // 2 chars for each byte
	Uint256 x(strncpy(xStr, &curvePointStr[0], size*2));
	Uint256 y(&curvePointStr[size*2]);
	delete xStr;

	unique_ptr<CurvePoint> cp(new CurvePoint(FieldInt(x), FieldInt(y)));

	return cp;
}

const Uint256 Transaction::DEFAULT_NONCE = Uint256("0000000000000000000000000000000000000000000000000000000000000002");
const size_t Transaction::KEY_SIZE = Uint256::NUM_WORDS * 8;
const size_t Transaction::ADDRESS_SIZE = Transaction::KEY_SIZE * 2; 
//const size_t Transaction::ADDRESS_SIZE = (Transaction::KEY_SIZE + 1) * 2; 

size_t Transaction::TX_SIZE() {
	// @fix use sizeof uint8_t ?
	static const size_t TX_SIZE = KEY_SIZE * 2 + 1;
	return TX_SIZE;
}

Bytes PublicKey::toBytes() const {
	return Transaction::serializeCurvePoint(curvePoint);
}

const string PublicKey::toString() const {
	return Utils::bytesToStr(toBytes());
}

PublicKey::PublicKey(const Bytes &keyBytes)
	: curvePoint(*Transaction::deserializeCurvePoint(keyBytes)) {}

PublicKey::PublicKey(const CurvePoint &cp) 
	: curvePoint(cp) {}

PublicKey::PublicKey(const char* address)
	: curvePoint(*Transaction::deserializeCurvePoint(address)) {}

bool PublicKey::operator ==(const PublicKey &key) const {
	if(curvePoint == key.curvePoint) 
		return true;
	return false;
}

PrivateKey::PrivateKey(Uint256 val)
	: value(val) {}

PrivateKey::PrivateKey(const char* key)
	: value(key) {}

Bytes PrivateKey::toBytes() const {
	Bytes key;
	size_t size = Uint256::NUM_WORDS * 4;
	uint8_t serial[size]; 

	value.getBigEndianBytes(serial); // fill serial with bytes from Uint256 val
	key.insert(key.begin(), serial, serial + size);

	return key;
}

const Uint256 PrivateKey::get() const {
	return value;
}

Signature::Signature(Uint256& r, Uint256& s)
	: r(r), s(s) {}

Signature::Signature()
	: r(), s() {}

Bytes Signature::toBytes() const {
	Bytes sig;

	size_t size = Uint256::NUM_WORDS * 4;
	uint8_t serial[size * 2]; 

	r.getBigEndianBytes(&serial[0]);
	s.getBigEndianBytes(&serial[size]);

	sig.insert(sig.begin(), serial, serial + (size*2));

	return sig;
}
