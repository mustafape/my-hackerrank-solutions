#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

/*-------------------------------------------------------------------*/
//	Vector-Erase
/*-------------------------------------------------------------------*/
typedef struct myRange
{
	unsigned int start;
	unsigned int end;
} myRange;

class myVectorEraseClass
{
	friend istream& getline(istream &input, myVectorEraseClass& obj);
	friend istream& getline(istream &input, myRange& obj);
private:
	int m_cap;
	std::vector<int> m_values;
	unsigned int m_erase_position;
	myRange m_range;
public:
	void setCapacity(int cap) 					{m_cap = cap;}
	int getCapacity()         					{return m_cap;}
	void push(int val)      					{m_values.push_back(val);}

	void erase(unsigned int val)
	{
		if(val > 0 && val < m_values.size())
		{
			m_values.erase(m_values.begin() + val-1);
			m_cap = m_values.size();
		}
	}

	void erase(myRange range)
	{
		if(range.start > 0 && range.start < m_values.size() && range.end > 0 && range.end < m_values.size())
		{
			m_values.erase(m_values.begin() + range.start-1, m_values.begin() + range.end-1);
			m_cap = m_values.size();
		}
	}

	void dump()
	{
		cout << getCapacity() << endl;
		for(int i=0; i<m_values.size(); ++i)
		{
			cout << m_values[i] << " ";
		}
		cout << endl;
	}
};

istream& getline(istream &input, myVectorEraseClass& obj)
{
	int value;

	for (int i=0; i<obj.getCapacity(); ++i)
	{
		input >> value;
		obj.push(value);
	}

	return input;
}

istream& getline(istream &input, myRange& obj)
{
	input >> obj.start >> obj.end;

	return input;
}

void
runVectorEraseChallenge()
{
	myVectorEraseClass myClass;
	unsigned int capacity;
	unsigned int erase_position;
	myRange erase_range;

	cin >> capacity;
	myClass.setCapacity(capacity);
	
	getline(cin, myClass);

	cin >> erase_position;
	myClass.erase(erase_position);

	getline(cin, erase_range);
	myClass.erase(erase_range);

	myClass.dump();
}
/*-------------------------------------------------------------------*/


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */  
    runVectorEraseChallenge();
    
    return 0;
}
