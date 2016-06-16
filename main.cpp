#include <iostream>
#include <cstdlib>
#include "big.h"
#include "compute.h"

using namespace std;

int main(){
	string N;
	cout<< "Input the big number N: " ;
	cin >> N;

	compute test(N);

	return 0;
}