#include <iostream>
#include <vector>
#include "big.h"

// constructors
big::big (string num){
	m_num = string_to_vector(num);
}

big::big(vector<bool>& y){
	for(size_t i =0, l =y.size(); i<l; i++){
		m_num.push_back(y[i]);
	}
}

big::big(size_t times){
	for(size_t i=0;i<times;i++){
		m_num.push_back(0);
	}
	m_num.push_back(1);
}

// private functions
vector<int> big::vector_div(vector<int>& vec){
	bool over = false;
	vector<int> to_return;
	for(size_t i=0, l=vec.size();i<l;i++){
		if(!over){
			if(vec[i]%2 == 1){
				over = true;
			}

			to_return.push_back(vec[i]/2);
		}else{
			if(vec[i]%2 == 0){
				over = false;
			}

			to_return.push_back( (vec[i]+10)/2 );
		}
	}

	if(to_return[0] == 0){
		to_return.erase(to_return.begin());
	}

	return to_return;
}

vector<bool> big::string_to_vector(string num){
	vector<int> dec;
	for(size_t i=0, l=num.size(); i<l; i++){
		switch(num[i]){
			case '0':
				dec.push_back(0);
				break;
			case '1':
				dec.push_back(1);
				break;
			case '2':
				dec.push_back(2);
				break;
			case '3':
				dec.push_back(3);
				break;
			case '4':
				dec.push_back(4);
				break;
			case '5':
				dec.push_back(5);
				break;
			case '6':
				dec.push_back(6);
				break;
			case '7':
				dec.push_back(7);
				break;
			case '8':
				dec.push_back(8);
				break;
			case '9':
				dec.push_back(9);
				break;
			default:
				throw;
		}
	}

	vector<bool> to_return;
	while(dec.size() != 0){
		to_return.push_back( dec[dec.size()-1] % 2 );
		dec = vector_div(dec);
	}

	return to_return;
}

big big::double_input_times (const big& y,int times){
	big to_return = y;

	reverse(to_return.m_num.begin(),to_return.m_num.end());
	for(int i=0; i<times; i++){
		to_return.m_num.push_back(0);
	}
	reverse(to_return.m_num.begin(),to_return.m_num.end());

	return to_return;
}

bool big::meLarger (const big& y){
	if(m_num.size() != y.m_num.size())
		return m_num.size() > y.m_num.size();

	for(size_t i=m_num.size() -1 ; i > 0; i--){
		if(m_num[i] > y.m_num[i])
			return true;
		else if(m_num[i] < y.m_num[i])
			return false;
	}

	return m_num[0] > y.m_num[0];
}


// public functions
big big::operator + (const big& y){
	bool over = false;
	bool y_larger = !meLarger(y);
	size_t l = (y_larger)? m_num.size() : y.m_num.size();
	size_t k = (!y_larger)? m_num.size() : y.m_num.size();

	vector<bool> to_return;
	for(size_t i=0; i<k; i++){
		if(i<l){
			if(m_num[i]){
				if(y.m_num[i]){
					to_return.push_back(over);
					over = true;
				}else{
					to_return.push_back(!over);
				}
			}else{
				if(y.m_num[i]){
					to_return.push_back(!over);
				}else{
					to_return.push_back(over);
					over = false;
				}
			}
		}else{
			if(y_larger){
				to_return.push_back(over != y.m_num[i]);
				over = over && y.m_num[i];
			}else{
				to_return.push_back(over != m_num[i]);
				over = over && m_num[i];
			}
		}
	}

	if(over){
		to_return.push_back(over);
	}

	return big(to_return);
}

big big::operator - (const big& y){
	if(*this < y)
		return big("0");

	bool over = false;
	vector<bool> to_return;

	bool y_larger = !meLarger(y);
	vector<bool> larger = y_larger ? y.m_num : m_num;
	vector<bool> smaller = y_larger? m_num : y.m_num;

	for(size_t i =0, l =larger.size(), k=smaller.size(); i<l; i++){
		if(i < k){
			if(larger[i]){
				if(smaller[i]){
					to_return.push_back(over);
				}else{
					to_return.push_back(!over);
					over = false;
				}
			}else{
				if(smaller[i]){
					to_return.push_back(!over);
					over = true;
				}else{
					to_return.push_back(over);
				}
			}
		}else{
			to_return.push_back(over != larger[i]);
			over = over > larger[i];
		}
	}

	while(!to_return.empty() && !to_return[to_return.size()-1] ){
		to_return.pop_back();
	}

	return big(to_return);
}

big big::operator * (const big& y){
	if(y.m_num.size() == 0 || m_num.size() == 0){
		return big("0");
	}

	big to_return("0");
	for(size_t i=0, l=m_num.size(); i<l; i++){
		if(m_num[i]){
			to_return = to_return + double_input_times(y,i);
		}
	}

	return to_return;
}

bool big::operator == (const big& y){
	if( !(y.m_num.size() == m_num.size()) )
		return false;
	for(size_t i=0, l=y.m_num.size(); i<l; i++){
		if(m_num[i] != y.m_num[i])
			return false;
	}

	return true;
}

bool big::operator > (const big& y){
	size_t m = m_num.size();
	size_t ym = y.m_num.size();

	if(m>ym)
		return true;
	if(m<ym)
		return false;
	
	for(size_t i=0;i<m;i++){
		if(m_num[m-i-1]>y.m_num[m-i-1])
			return true;
		if(m_num[m-i-1]<y.m_num[m-i-1])
			return false;
	}

	return false;
}

bool big::operator < (const big& y){
	big temp = y;
	if(temp > *this)
		return true;
	return false;
}

big big::operator = (string num){
	m_num = string_to_vector(num);
	return *this;
}

big big::operator % (const big& y){
	big temp = *this;
	big yp = y;

	while(temp > y){
		if( !(double_input_times(yp,1) > temp) ){
			yp = double_input_times(yp,1);
		}else{
			temp = temp - yp;
			yp = y;
		}
	}

	if(temp == y)
		temp = "0";

	return temp;
}

void big::div (){
	if(!m_num.empty())
		m_num.erase(m_num.begin());
}

bool big::divable(){
	return m_num[0] == 0;
}

size_t big::div_many(){
	size_t to_return = 0;
	if(m_num[0])
		return to_return;

	reverse(m_num.begin(),m_num.end());
	while(!m_num.back()){
		m_num.pop_back();
		to_return++;
	}
	reverse(m_num.begin(),m_num.end());

	return to_return;
}

string big::getBinString(){
	if(m_num.size() == 0){
		return "0";
	}

	char* to_return = new char [m_num.size() + 1];
	for(size_t i=0, l= m_num.size(); i<l; i++){
		to_return[l-i-1] = (m_num[i])? '1':'0';
	}

	to_return[m_num.size()] = '\0';

	return to_return;
}