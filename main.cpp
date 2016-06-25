#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector>
#include "big.h"
#include "compute.h"
#include "computeLegacy.h"

using namespace std;

int main(){
	ifstream inputFile;
	inputFile.open("primes.txt");

	ofstream outputFile;
	outputFile.open("exp.csv");

	if(outputFile && inputFile){
		outputFile << "log2(N),Time Using Legacy (sec),Time Using New (sec)" <<endl;
	}else{
		cout<< "Excel file opening error!"<<endl;
		return -1;
	}

	cout<< "Creating primes list by reading file... " << flush;
	
	vector<big> primes;
	string temp;
	while(getline(inputFile,temp)){
		cout<<"!\t"<< temp <<flush;
		big tempBig(temp);
		primes.push_back(tempBig);
	}
	inputFile.close();

	cout<<" DONE"<<endl;

	vector<big> ns;
	cout << "Creating Testing Numbers (Ns)... " << endl;
	
	for(size_t i=0, l=primes.size() - 1; i<l; i++){
		ns.push_back(primes[i] * primes[i+1]);
	}

	cout<< " DONE" << endl;

	for(size_t i=0, l=ns.size(); i<l; i++){
		compute test(ns[i]);
		computeLegacy testLegacy(ns[i]);

		outputFile << ns[i].getBinVector().size() << "," << testLegacy.getTimeSec() << "," << test.getTimeSec()<<endl;
	}

	outputFile.close();

	return 0;
}