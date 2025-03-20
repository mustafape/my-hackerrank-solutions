#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class myVectorInput
{
	friend istream& getline(istream &input, myVectorInput& inp);
private:
	std::vector<int> m_values;
	int m_cap;
public:
	std::vector<int> getValues() {return m_values;}
	void setCapacity(int cap) {m_cap = cap;}
	int getCapacity()         {return m_cap;}
	void push(int value)      {m_values.push_back(value);}
	void sort()			  	  {std::sort(m_values.begin(), m_values.end());}
	void dump()
	{
		for(int i=0; i<m_cap; ++i)
		{
			cout << m_values[i] << " ";
		}
		cout << endl;
	}
};

istream& getline(istream &input, myVectorInput& inp)
{
	int value;

	for (int i=0; i<inp.getCapacity(); ++i)
	{
		input >> value;
		inp.push(value);
	}

	return input;
}

void
testVectorInput()
{
	myVectorInput testVectorInput;

	int capacity;

	cin >> capacity;

	testVectorInput.setCapacity(capacity);
	
	getline(cin, testVectorInput);
	testVectorInput.sort();
	testVectorInput.dump();
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    testVectorInput();
    
    return 0;
}
