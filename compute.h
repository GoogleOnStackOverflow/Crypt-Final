#include <iostream>
#include <utility>
#include "big.h"

using namespace std;

#ifndef COMPUTE
#define COMPUTE

class compute {
	big N;
	big L;

	vector< pair<big,big> > mapping;

	pair<big,big> largest_less(const big&);
	pair<big,big> largest_less_mapping(const big&, vector< pair<big,big> >);

	big sizet_to_big(size_t);
	char sizet_to_char(size_t s);
	size_t big_to_sizet(const big&);
	void showLoopTimes(int);

	bool remain_one(size_t,const big&);

	string fileNameCreater(string);
public:
	compute(string);
	big& getPhy(){ return L; };
};

#endif