#include <iostream>
#include <utility>
#include "big.h"

using namespace std;

#ifndef COMPUTELEGACY
#define COMPUTELEGACY

class computeLegacy {
	float time_in_sec;
	big N;

	vector< pair<big,big> > mapping;

	pair<big,big> largest_less(const big&);
	pair<big,big> largest_less_mapping(const big&, vector< pair<big,big> >);

	char* sizet_to_string(size_t);
	big sizet_to_big(size_t);
	char sizet_to_char(size_t s);
	size_t big_to_sizet(const big&);
	void showLoopTimes(int);

	bool remain_one(size_t,const big&);

	string fileNameCreater(string);
public:
	computeLegacy(string);
	computeLegacy(big);
	float getTimeSec(){ return time_in_sec; };
};

#endif