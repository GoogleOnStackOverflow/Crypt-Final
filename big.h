#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;

#ifndef BIG
#define BIG 
class big
{
	vector<bool> m_num;

	vector<int> vector_div(vector<int>&);
	vector<bool> string_to_vector(string);

	bool meLarger(const big&);
public:
	big() {};
	big(string);
	big(vector<bool>&);
	big(size_t);

	big operator + (const big&);
	big operator - (const big&);
	big operator * (const big&);
	big operator = (string);
	bool operator == (const big&);
	bool operator > (const big&);
	bool operator < (const big&);
	big operator % (const big&);
	big double_input_times(const big&,int);

	void div ();
	bool divable ();
	size_t div_many ();

	vector<bool> getBinVector() { return m_num; };
	string getBinString();
};

#endif