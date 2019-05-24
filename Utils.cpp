#include "Utils.hpp"

void Utils::appendBytes(Bytes &orig, const Bytes &toAppend) {
	Bytes tmp;

	// @fix does this reliably check if orig and toAppend refernce same vector?
	if(&orig == &toAppend) {
		tmp = Bytes(toAppend.begin(), toAppend.end());
	} else {
		tmp = toAppend;
	}
	orig.insert(orig.end(), tmp.begin(), tmp.end());
}	

void Utils::appendBytesArr(Bytes &orig, const uint8_t *toAppend, const size_t size) {
	orig.insert(orig.end(), toAppend, toAppend + size);
}	

Bytes Utils::hexStrToBytes(const char *str) {
	Bytes result;
	size_t length = std::strlen(str);
	assert(length % 2 == 0);
	for (size_t i = 0; i < length; i += 2) {
		unsigned int temp;
		std::sscanf(&str[i], "%02x", &temp);
		result.push_back(static_cast<std::uint8_t>(temp));
	}
	return result;
}

Bytes Utils::Uint256ToBytes(const Uint256 &value) {
	Bytes bytes;
	size_t size = Uint256::NUM_WORDS * 4;
	uint8_t serial[size]; 

	value.getBigEndianBytes(serial); // fill serial with bytes from Uint256 val
	bytes.insert(bytes.begin(), serial, serial + size);

	return bytes;
}

Bytes Utils::hashToBytes(const Sha256Hash &hash) {
	return Bytes(hash.value, hash.value + Sha256Hash::HASH_LEN); 
}

string Utils::bytesToStr(const Bytes &orig) {
	string str = "";
	for(auto &b : orig) {
		str += hexify<uint8_t>(b);
	}
	return str;
}


string Utils::toStr(const Sha256Hash& hash) {
	return bytesToStr(hashToBytes(hash));
}

string Utils::toStr(const Uint256& value) {
	return bytesToStr(Uint256ToBytes(value));
}
/*
   string toStr(const Uint256& value);
   string toStr(const CurvePoint& curvePoint);
   */

// @param length: number of bytes to display at either end
string Utils::abridgeBytes(const Bytes &bytes, size_t length) {
	assert(bytes.size() >= length*2);
	Bytes::const_iterator front = bytes.begin();
	Bytes::const_iterator back = bytes.end();
	--back;

	Bytes l, r;
	// @fix use insert operation O(1)
	//l.insert(l.begin(), bytes.begin(), bytes.begin() + length);
	//r.insert(l.begin(), back - length, back);
	//r.insert(l.begin(), bytes.end() - length, bytes.end());
	for(int i=0; i<length; i++, ++front, --back) {
		l.push_back(*front);
		r.insert(r.begin(), *back);
	}

	return "0x" + bytesToStr(l) + "..." + bytesToStr(r);
}
