#include <iostream>
using namespace std;

int main() {
	cout << "Sizeof int: " << sizeof(int) << endl;

	const int size = 64;
	int arr[size];
	for(int i=0; i<size; i++) {
		int tmp = i >> 3;
		arr[i >> 3] = i;
		if(1) {
			cout << "i: " << i << ",\t";
			cout << "i >> 3: " << tmp << endl;
		}
	}
}
