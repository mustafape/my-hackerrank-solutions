/**
 * @file day28-regex-patterns-intro_to_databases.cpp
* - testDay28 function to demonstrate the usage of the emailsDB class by reading input, filtering, sorting, and
 *   dumping records. This edition includes a strategy pattern for sorting records as well as use of lambdas.

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
#include <iomanip>
#include <vector>
#include <string>
#include <cmath>
#include <cstdio>
#include <memory>
#include <string>

using namespace std;

typedef struct aRecord
{
	string m_firstName;
	string m_emailId;
	bool m_hidden = false;
} aRecord;

// Sort Strategy Interface
class SortStrategy {
    public:
		enum SortOrder {so_ASC, so_DESC, so_UNDEFINED_SORT_ORDER};					//	Sort order
		enum SortCriteria {sc_BY_NAME, sc_BY_EMAIL, sc_UNDEFINED_SORT_CRITERIA};	//	Sort criteria

		virtual void execute(vector<aRecord>& records, SortOrder order) = 0; // Pure virtual function
		virtual ~SortStrategy() {} // Virtual destructor
};

/*-------------------------------------------------------------------*/
//	Day 28: RegEx, Patterns, and Intro to Databases
/*-------------------------------------------------------------------*/
class emailsDB
{
	friend istream& getline(istream &input, emailsDB& obj);
	private:
		vector <aRecord> m_record_collection;			// Collection of records
        std::unique_ptr<SortStrategy> m_sortStrategy;	// Sort Strategy

    public:
		enum dumpCriteria {dc_NAME, dc_EMAIL, dc_ALL};	//	criteria for dump
		enum filterCriteria {fc_INACTIVE, fc_ACTIVE};	//	criteria for filtering

        void setSortStrategy(unique_ptr<SortStrategy> strategy) {
            m_sortStrategy = move(strategy);
        }

        void executeSort(SortStrategy::SortOrder order) {
            if (m_sortStrategy) {
                m_sortStrategy->execute(m_record_collection, order);
            } else {
                cout << "No sort strategy set" << endl;
            }
        }

		void setCapacity(int value) { m_record_collection.reserve(value); };
		int getCapacity() { return m_record_collection.size(); };
		void push(aRecord* item) { m_record_collection.push_back(*item); };
		int filterByText(string textToContain);
		int dump(dumpCriteria criteria, filterCriteria filter);
};


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
emailsDB::dump(dumpCriteria criteria, filterCriteria filter = fc_INACTIVE)
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

// Concrete Sort Strategy for sorting by name in requested order
class SortByName : public SortStrategy {
public:
    void execute(vector<aRecord>& records, SortOrder order) override {
        sort(records.begin(), records.end(), [order](const aRecord& lhs, const aRecord& rhs) {
            return ((order == SortOrder::so_ASC) ? (lhs.m_firstName < rhs.m_firstName) : (lhs.m_firstName > rhs.m_firstName));
        });
    }
};

// Concrete Sort Strategy for sorting by email in requested order
class SortByEmail : public SortStrategy {
public:
	void execute(vector<aRecord>& records, SortOrder order) override {
		sort(records.begin(), records.end(), [order](const aRecord& lhs, const aRecord& rhs) {
			return (order == SortOrder::so_ASC) ? lhs.m_emailId < rhs.m_emailId : lhs.m_emailId > rhs.m_emailId;
		});
	}
};

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
	myDB.setSortStrategy(std::make_unique<SortByName>());
	myDB.executeSort(SortStrategy::so_ASC);
	myDB.dump(emailsDB::dc_NAME, emailsDB::fc_ACTIVE);

	// Below is another example of how to use the SortByEmail strategy, descending order, and dumping email IDs
	//myDB.setSortStrategy(std::make_unique<SortByEmail>());
	//myDB.executeSort(SortStrategy::so_DESC);
	//myDB.dump(emailsDB::dc_EMAIL);
}

/*-------------------------------------------------------------------*/

int main(){
    testDay28();

    return 0;
}
