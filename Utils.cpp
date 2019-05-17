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

/*void Utils::appendBytes(Bytes *orig, Bytes *toAppend) {
	Bytes* tmp;
	bool flag = false;

	if(orig == toAppend) {
		tmp = new Bytes(toAppend);
		flag = true;
	} else {
		tmp = toAppend;
	}
	orig->insert(orig->end(), tmp->begin(), tmp->end());

	if(flag) 
		delete(tmp);
}	*/
