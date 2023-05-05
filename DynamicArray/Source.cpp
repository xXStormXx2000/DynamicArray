#include "DynamicArray.h"
#include <iostream>


DynamicArray<int> f(DynamicArray<int> a) {
	return a;
}


int main() {
	DynamicArray<int> a = { 1,2,3,4,3,4,5,43,2,1 }, b = a, c(10), d;
	d = f({ 1,2,3,4,3,4,5,43,2,1 });
	DynamicArray<int> m(f({ 1,2,3,4,3,4,5,43,2,1 }));
	for (int i : b) std::cout << i << " ";
	return 0;
}