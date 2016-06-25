#include <iostream>
#include <vector>
#include <utility>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include "big.h"
#include "compute.h"

// constructor
compute::compute (big input){
	cout<<"\n\nComputing Phy by New Algorithm... "<<endl;
	
	clock_t t0,t1,t2;
	t0 = clock();
	cout<< "Creating Bitwise numbers needed..." <<flush;

	N = input;

	big remainder_base( N.getBinVector().size() *8);
	big remainder_base_size = sizet_to_big( N.getBinVector().size() *8);
	remainder_base = remainder_base % N;
	big two("2");
	big zero("0");

	big remain_time = N;
	big starter_time = remainder_base_size;
	big starter_remainder_base = remainder_base;
	big mod_remainder("1");

	cout<< " DONE\nComputing 2^N (mod N)..."<<endl;
	bool mapped = false;

	mapping.push_back(make_pair(remainder_base_size,remainder_base));

	cout<< "\tCreating Mappings for fast computation..."<<flush;

	while(!mapped){
		if( !(remainder_base_size.double_input_times(remainder_base_size,1) < remain_time ) ){
			mapped = true;
		}else{
			//main loop
			remainder_base = (remainder_base * remainder_base) % N;
			remainder_base_size = remainder_base_size.double_input_times(remainder_base_size,1);
			mapping.push_back(make_pair(remainder_base_size,remainder_base));
		}
	}

	cout<<" DONE\n\tNow Computing 2^N (mod N)..."<<flush;
	while( !(remain_time == zero) ){
		if( !(remain_time > starter_time) ){
			//do the remaining
			cout<<"\n\tLoop Part DONE. Computing the remainings..."<<flush;
			mod_remainder = ( mod_remainder * big(big_to_sizet(remain_time)) ) % N;
			remain_time = zero;
		}else{
			// restart from start_time
			pair<big, big> cut_pair = largest_less(remain_time);
			mod_remainder = ( mod_remainder * (cut_pair.second) ) % N;
			remain_time = remain_time - (cut_pair.first);
		}
	}

	t1 = clock();
	cout<<" DONE\nTime Used to find L: " << (float)(((float)t1 - (float)t0)/ CLOCKS_PER_SEC) <<" secs"<<endl;
	cout<< "Computing Phy(N)... "<<flush;
	L = mod_remainder;

	// L = L + N
	L = L + N;
	big Phy = N;
	big one("1");

	mapping.clear();

	big cutTimeBig;
	while(!(L == one)){
		size_t cutTime = L.div_many();

		if(cutTime != 0){
			for(size_t i=0;i<cutTime;i++){
				Phy = Phy - one;
			}
		}else if(!(L == one)){
			L = L + N;
		}
	}

	t2 = clock();
	cout<<" DONE\nPhy(N) = "<<big_to_sizet(Phy)<< " (in size_t, which may overflow)"<<endl;

	float totalTimeInSec = ((float)t2 - (float)t0)/ CLOCKS_PER_SEC;
	cout<<"Total time used to find Phy(N): "<< totalTimeInSec <<" secs"<<endl;

	time_in_sec = totalTimeInSec;
}

compute::compute (string input){
	cout<<"\n\nComputing Phy by New Algorithm... "<<endl;
	
	clock_t t0,t1,t2;
	t0 = clock();
	cout<< "Creating Bitwise numbers needed..." <<flush;

	N = input;

	big remainder_base( N.getBinVector().size() *8);
	big remainder_base_size = sizet_to_big( N.getBinVector().size() *8);
	remainder_base = remainder_base % N;
	big two("2");
	big zero("0");

	big remain_time = N;
	big starter_time = remainder_base_size;
	big starter_remainder_base = remainder_base;
	big mod_remainder("1");

	cout<< " DONE\nComputing 2^N (mod N)..."<<endl;
	int totalLoops = 0;
	int loopTimes = 1;
	bool mapped = false;

	mapping.push_back(make_pair(remainder_base_size,remainder_base));

	cout<< "\tCreating Mappings for fast computation... Loops: "<<flush;
	while(!mapped){
		showLoopTimes(loopTimes++);
		++totalLoops;
		if( !(remainder_base_size.double_input_times(remainder_base_size,1) < remain_time ) ){
			mapped = true;
		}else{
			//main loop
			remainder_base = (remainder_base * remainder_base) % N;
			remainder_base_size = remainder_base_size.double_input_times(remainder_base_size,1);
			mapping.push_back(make_pair(remainder_base_size,remainder_base));
		}
	}

	loopTimes = 1;
	cout<<" DONE\n\tNow Computing 2^N (mod N)... Loops: "<<flush;
	while( !(remain_time == zero) ){
		showLoopTimes(loopTimes++);
		++totalLoops;
		if( !(remain_time > starter_time) ){
			//do the remaining
			cout<<"\n\tLoop Part DONE. Computing the remainings..."<<flush;
			mod_remainder = ( mod_remainder * big(big_to_sizet(remain_time)) ) % N;
			remain_time = zero;
		}else{
			// restart from start_time
			pair<big, big> cut_pair = largest_less(remain_time);
			mod_remainder = ( mod_remainder * (cut_pair.second) ) % N;
			remain_time = remain_time - (cut_pair.first);
		}
	}

	t1 = clock();
	cout<<" DONE\nTime Used to find L: " << (float)(((float)t1 - (float)t0)/ CLOCKS_PER_SEC) <<" secs"<<endl;
	cout<< "Computing Phy(N)... Loops: "<<flush;
	L = mod_remainder;

	// L = L + N
	L = L + N;
	big Phy = N;
	big one("1");

	loopTimes = 1;
	mapping.clear();

	big cutTimeBig;
	while(!(L == one)){
		showLoopTimes(loopTimes++);
		++totalLoops;

		size_t cutTime = L.div_many();

		if(cutTime != 0){
			for(size_t i=0;i<cutTime;i++){
				Phy = Phy - one;
			}
		}else if(!(L == one)){
			L = L + N;
		}
	}

	t2 = clock();
	cout<<" DONE\nPhy(N) = "<<big_to_sizet(Phy)<< " (in size_t, which may overflow)"<<endl;

	float totalTimeInSec = ((float)t2 - (float)t0)/ CLOCKS_PER_SEC;
	cout<<"Total time used to find Phy(N): "<< totalTimeInSec <<" secs"<<endl;
	cout<<"Total Loops: " << totalLoops <<endl;

	time_in_sec = totalTimeInSec;
}

// private function
char* compute::sizet_to_string(size_t s){
	big return_big;
	vector<char> temp;
	while(s != 0){
		temp.push_back(sizet_to_char(s % 10));
		s = s/10;
	}

	char* to_return = new char [temp.size()];
	for(size_t i=0, l=temp.size();i<l;i++){
		to_return[i] = temp[l-i-1];
	}

	return to_return;
}

big compute::sizet_to_big(size_t s){
	big return_big(sizet_to_string(s));

	return return_big;
}

char compute::sizet_to_char(size_t s){
	switch(s){
		case 0:
			return '0';
		case 1:
			return '1';
		case 2:
			return '2';
		case 3:
			return '3';	
		case 4:
			return '4';
		case 5:
			return '5';
		case 6:
			return '6';
		case 7:
			return '7';
		case 8:
			return '8';
		case 9:
			return '9';
		default:
			return '0';
	}
}

pair<big, big> compute::largest_less(const big& y){
	big temp = y;
	if(mapping.size() == 1)
		return mapping[0];

	for(size_t i =0, l=mapping.size();i<l;i++){
		if( !(temp.double_input_times(mapping[i].first,1) < temp) )
			return mapping[i];
	}

	return make_pair(big("0"),big("0"));
}

pair<big, big> compute::largest_less_mapping(const big& y, vector< pair<big, big> > _map){
	big temp = y;
	if(_map.size() == 1)
		return _map[0];

	for(size_t i =0, l=_map.size();i<l;i++){
		if( !(temp.double_input_times(_map[i].first,1) < temp) )
			return _map[i];
	}

	return make_pair(big("0"),big("0"));
}

size_t compute::big_to_sizet(const big& y){
	size_t to_return = 0;
	size_t times = 1;
	big temp = y;
	for(size_t i=0, l = temp.getBinVector().size();i<l;i++){
		to_return += temp.getBinVector()[i]? times:0;
		times *= 2;
	}

	return to_return;
}

void compute::showLoopTimes(int times){
	int tendi =0;
	int temp = times;
	bool first = true;
	while(temp != 0){
		if(first) 
			first = (temp == 1)? first: (( temp%10==0 )? first:false);
		temp = temp /10;
		tendi++;
	}
	if(first) tendi--;
	for(int i=0;i<tendi;i++)
		cout<<'\b'<<flush;
	cout<<times<<flush;
}

bool compute::remain_one(size_t times, const big& y){
	size_t base = 1;
	for(size_t i=0;i<times;i++){
		base *= 2;
	}

	cout<<"Computing "<< base <<"^Phy(N)' (mod N)... "<<endl;
	big mod = y;
	big remain_time = mod * sizet_to_big(times);
	cout<<"remain time: "<<big_to_sizet(remain_time)<<endl;

	big remainder_base( N.getBinVector().size() +1);
	big remainder_base_size = sizet_to_big( N.getBinVector().size() +1);
	remainder_base = remainder_base % N;
	big two("2");
	big zero("0");

	big starter_time = remainder_base_size;
	big starter_remainder_base = remainder_base;
	big mod_remainder("1");

	int totalLoops = 0;
	int loopTimes = 1;
	bool mapped = false;
	vector< pair<big,big> > lmap;

	lmap.push_back(make_pair(remainder_base_size,remainder_base));

	cout<< "\tCreating Mappings for fast computation... Loops: "<<flush;
	while(!mapped){
		showLoopTimes(loopTimes++);
		++totalLoops;
		if( !(remainder_base_size.double_input_times(remainder_base_size,1) < remain_time ) ){
			mapped = true;
		}else{
			//main loop
			remainder_base = (remainder_base * remainder_base) % N;
			remainder_base_size = remainder_base_size.double_input_times(remainder_base_size,1);
			lmap.push_back(make_pair(remainder_base_size,remainder_base));
		}
	}

	loopTimes = 1;
	cout<<" DONE\n\tNow Computing "<< base <<"^Phy(N)' (mod N)... Loop: "<<flush;
	while( !(remain_time == zero) ){
		showLoopTimes(loopTimes++);
		++totalLoops;
		if( !(remain_time > starter_time) ){
			//do the remaining
			cout<<"\n\tLoop Part DONE. Computing the remainings..."<<flush;
			mod_remainder = ( mod_remainder * big(big_to_sizet(remain_time)) ) % N;
			remain_time = zero;
		}else{
			// restart from start_time
			pair<big, big> cut_pair = largest_less_mapping(remain_time, lmap);
			mod_remainder = ( mod_remainder * (cut_pair.second) ) % N;
			remain_time = remain_time - (cut_pair.first);
		}
	}

	cout<< " DONE"<<endl;
	return mod_remainder == big("1");
}