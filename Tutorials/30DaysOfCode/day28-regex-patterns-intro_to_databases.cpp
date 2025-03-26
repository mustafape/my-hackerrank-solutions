/**
 * @file day28-regex-patterns-intro_to_databases.cpp
* - testDay28 function to demonstrate the usage of the emailsDB class by reading input, filtering, sorting, and
 *   dumping records.
 * 
 * The main function calls the testDay28 function to execute the program.
 * 
 * @note This program is part of a series of coding challenges and exercises.
 * 
 * @date 2023-10-05
 */
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

#include <iomanip>
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
	bool m_hidden = false;
} aRecord;

class emailsDB
{
	friend istream& getline(istream &input, emailsDB& obj);
	private:
		vector <aRecord> m_record_collection;
	public:
		enum SortOrder {
			so_ASC,
			so_DESC,
			so_UNDEFINED_SORT_ORDER
		};
		
		enum SortCriteria {
			sc_BY_NAME,
			sc_BY_EMAIL,
			sc_UNDEFINED_SORT_CRITERIA
		};

		enum dumpCriteria {
			dc_NAME,
			dc_EMAIL,
			dc_ALL
		};
		
		enum filterCriteria {
			fc_INACTIVE,
			fc_ACTIVE
		};	
		
		void setCapacity(int value) { m_record_collection.reserve(value); };
		int getCapacity() { return m_record_collection.size(); };
		void push(aRecord* item) { m_record_collection.push_back(*item); };
		int filterByText(string textToContain);
		int sortByCriteria(SortCriteria criteria, SortOrder order);
		int dump(dumpCriteria criteria, filterCriteria filter);
};

// Sort Container by name function
bool sortByNameASC(const aRecord &lhs, const aRecord &rhs) { return lhs.m_firstName < rhs.m_firstName; }
bool sortByNameDESC(const aRecord &lhs, const aRecord &rhs) { return lhs.m_firstName > rhs.m_firstName; }

// Sort Container by eMail function
bool sortByeMailASC(const aRecord &lhs, const aRecord &rhs) { return lhs.m_emailId < rhs.m_emailId; }
bool sortByeMailDESC(const aRecord &lhs, const aRecord &rhs) { return lhs.m_emailId > rhs.m_emailId; }

/**
 * Filters the email records by hiding those that do not contain the specified text.
 *
 * This function iterates through the collection of email records and hides any record
 * whose email ID does not contain the specified text. The hiding is done by setting
 * the `m_hidden` attribute of the record to `true`.
 *
 * @param textToContain The text that should be contained in the email ID for the record
 *                      to remain visible.
 * @return Always returns 0.
 */
int
emailsDB::filterByText(string textToContain) { 
	for(int i=0; i<m_record_collection.size(); i++) {
		if(m_record_collection[i].m_emailId.find(textToContain) == std::string::npos)
			m_record_collection[i].m_hidden = true;
	}

	return 0;
}

/**
 * @brief Sorts the email records in the database based on the given criteria and order.
 * 
 * @param criteria The criteria by which to sort the records. It can be either sc_BY_NAME or sc_BY_EMAIL.
 * @param order The order in which to sort the records. It can be either so_ASC for ascending or so_DESC for descending.
 * @return int Returns 0 if the sorting is successful, or -1 if the criteria is invalid.
 */
int
emailsDB::sortByCriteria(SortCriteria criteria, SortOrder order)
{
	int result = 0;

	if(criteria == sc_BY_NAME)
		sort(m_record_collection.begin(), m_record_collection.end(), (order == so_ASC) ? sortByNameASC : sortByNameDESC);
	else if(criteria == sc_BY_EMAIL)
		sort(m_record_collection.begin(), m_record_collection.end(), (order == so_ASC) ? sortByeMailASC : sortByeMailDESC);
	else
		result = -1;
	
	return result;
}


/**
 * Dumps the email records based on the specified criteria and filter.
 *
 * @param criteria The criteria for dumping the records. It can be one of the following:
 *                 - dc_NAME: Dump only the names.
 *                 - dc_EMAIL: Dump only the email IDs.
 *                 - dc_ALL: Dump both names and email IDs.
 * @param filter The filter criteria for dumping the records. It can be one of the following:
 *               - fc_ACTIVE: Dump only active records (non-hidden).
 *               - Other values: Dump all records.
 * @return Returns 0 on success, or -1 if an invalid criteria is provided.
 */
int
emailsDB::dump(dumpCriteria criteria, filterCriteria filter)
{
	int result = 0;

	for (int i=0; i<m_record_collection.size(); ++i) {
		if(filter == fc_ACTIVE && m_record_collection[i].m_hidden)
			continue;
		else{
			if(criteria == dc_NAME)
				cout << m_record_collection[i].m_firstName << endl;
			else if(criteria == dc_EMAIL)
				cout << m_record_collection[i].m_emailId << endl;
			else if(criteria == dc_ALL)
				cout << m_record_collection[i].m_firstName << " " << m_record_collection[i].m_emailId << endl;
			else
				result = -1;
		}
	}

	return result;
}

/**
 * @brief Extracts a record from the input stream and adds it to the emails database.
 * 
 * This function reads a first name and an email ID from the input stream, creates
 * a record with these values, sets the hidden flag to false, and then pushes the
 * record into the provided emails database.
 * 
 * @param input The input stream to read from.
 * @param obj The emails database to which the record will be added.
 * @return The input stream after extraction.
 */
istream& getline(istream &input, emailsDB& obj)
{
	aRecord record;
	input >> record.m_firstName >> record.m_emailId;
	record.m_hidden = false;
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

	myDB.filterByText("@gmail");
	myDB.sortByCriteria(emailsDB::sc_BY_NAME, emailsDB::so_ASC);
	myDB.dump(emailsDB::dc_NAME, emailsDB::fc_ACTIVE);
}

/*-------------------------------------------------------------------*/

int main(){
    testDay28();

    return 0;
}
