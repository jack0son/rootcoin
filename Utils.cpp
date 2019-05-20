#include "Utils.hpp"

void Utils::appendBytesArr(
	Bytes &orig, 
	const uint8_t *toAppend, 
	const size_t size) 
{
	orig.insert(orig.end(), toAppend, toAppend + size);
}	

	
// @fix improper use of smart pointers
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

Bytes Utils::Uint256Bytes(const Uint256 &value) {
	Bytes bytes;
	size_t size = Uint256::NUM_WORDS * 4;
	uint8_t serial[size]; 

	value.getBigEndianBytes(serial); // fill serial with bytes from Uint256 val
	bytes.insert(bytes.begin(), serial, serial + size);

	return bytes;
}

Bytes Utils::strBytes(const char *str) {
	return Bytes(str, str + std::strlen(str));
}

string Utils::bytesToStr(const Bytes &orig) {
	string str = "";
	for(auto &b : orig) {
		str += hexify<uint8_t>(b);
	}
	return str;
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
