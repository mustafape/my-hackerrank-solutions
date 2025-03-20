#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;

#include <iostream>
#include <iomanip>
#include <algorithm>    // std::sort
#include <vector>
#include <string>
#include <cmath>
#include <cstdio>

/*-------------------------------------------------------------------*/
//	Day 28: RegEx, Patterns, and Intro to Databases
/*-------------------------------------------------------------------*/
typedef struct aRecord
{
	string m_firstName;
	string m_emailId;
} aRecord;

class emailsDB
{
	friend istream& getline(istream &input, emailsDB& obj);
	private:
		vector <aRecord> m_record_collection;
	public:
		enum SortOrder{
			so_ASC,
			so_DESC
		};
		void setCapacity(int value) { m_record_collection.reserve(value); };
		int getCapacity() { return m_record_collection.size(); };
		void push(aRecord* item) { m_record_collection.push_back(*item); };
		void sortByCriteria(SortOrder order, string textToContain);
		void dump();
};

// Sort Container by name function
bool sortByNameASC(const aRecord &lhs, const aRecord &rhs) { return lhs.m_firstName < rhs.m_firstName; }
bool sortByNameDESC(const aRecord &lhs, const aRecord &rhs) { return lhs.m_firstName > rhs.m_firstName; }

// Sort Container by eMail function
bool sortByeMailASC(const aRecord &lhs, const aRecord &rhs) { return lhs.m_emailId < rhs.m_emailId; }
bool sortByeMailDESC(const aRecord &lhs, const aRecord &rhs) { return lhs.m_emailId > rhs.m_emailId; }

void
emailsDB::sortByCriteria(SortOrder order, string textToContain)
{
	for(int i=m_record_collection.size()-1; i>=0; --i)
	{
		if(m_record_collection[i].m_emailId.find(textToContain) == std::string::npos)
		{
			m_record_collection.erase(m_record_collection.begin() + i);
		}
	}
	
	if(order == so_ASC)
	{
		sort(m_record_collection.begin(), m_record_collection.end(), sortByNameASC);
	}
	else if(order == so_DESC)
	{
		sort(m_record_collection.begin(), m_record_collection.end(), sortByNameDESC);
	}
}

void
emailsDB::dump()
{
	for (int i=0; i<m_record_collection.size(); ++i)
	{
		cout << m_record_collection[i].m_firstName << endl;
	}
}

istream& getline(istream &input, emailsDB& obj)
{
	aRecord record;

	input >> record.m_firstName >> record.m_emailId;
	obj.push(&record);

	return input;
}

void testDay28()
{
	emailsDB myDB;
	
	int capacity;
	cin >> capacity;
	myDB.setCapacity(capacity);

	for(int i=0; i<capacity; ++i)
	{
		getline(cin, myDB);
	}

	myDB.sortByCriteria(emailsDB::so_ASC, "@gmail");
	myDB.dump();
}

/*-------------------------------------------------------------------*/

int main(){
    testDay28();

    return 0;
}
