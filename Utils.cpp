#include "Utils.hpp"

char* Utils::intToHexStr(uint8_t &val) {
	char *ch = new char[1];
	ch[0] = 'c';
	return ch;
}

// @fix improper use of smart pointers
void Utils::appendBytes(shared_ptr<Bytes> orig, const shared_ptr<Bytes> toAppend) {
	shared_ptr<Bytes> tmp;

	if(orig.get() == toAppend.get()) {
		tmp = unique_ptr<Bytes>(new Bytes(toAppend->begin(), toAppend->end()));
	} else {
		tmp = toAppend;
	}
	orig->insert(orig->end(), tmp->begin(), tmp->end());
}	

Bytes asciiBytes(const char *str) {
	return Bytes(str, str + std::strlen(str));
}

Bytes hexBytes(const char *str) {
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
