#include "Uint256.hpp"
#include <iostream> 

//Uint256 Uint256();
Uint256 ZERO = Uint256::ZERO;

void print_bn(Uint256 bn) {
	for(int i=0; i<Uint256::NUM_WORDS; i++) {
		std::cout << bn.value[i];

	}

}

void other() {
	using namespace std;
	
	cout << "Zero (bignum): "; print_bn(ZERO);
	cout << endl << "One (bignum): "; print_bn(Uint256::ONE);
	cout << endl;

}


int main() {
	// Str_len == 64: bignum must receive value for every byte;
	// Hex digits
	const char hexStr[] = "DEADBEEFDEADBEEFDEADBEEFDEADBEEFDEADBEEFDEADBEEFDEADBEEFDEADBEEF";


	Uint256 tmp(hexStr);
	std::cout << "A Uint256 (bignum): ";

	print_bn(tmp);
	std::cout << std::endl;

	other();



	return 0;
}



