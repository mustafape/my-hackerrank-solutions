/*-------------------------------------------------------------------*/
//	Day 28: RegEx, Patterns, and Intro to Databases v3.0
/*-------------------------------------------------------------------*/
// @file day28-regex-patterns-intro_to_databases-v3.0.cpp
//
// testDay28 function to demonstrate the usage of the EmailsDBTable class by reading input, filtering, sorting, and
// dumping records. 
// The program implements a simple email database system that allows filtering and sorting of records based on
// user-defined criteria. It uses a strategy pattern for sorting and lambda functions for custom sorting.
//
// This edition of the solution demos:
//		- strategy pattern for sorting records.
//		- use of lambda functions for custom sorting.
//		- filter records based on email and name.
//		- use of unique_ptr for memory management.
//		- use of STL containers like vector and string.
//		- use of enums for filter types and sort criteria.
//		- use of friend function to access private members of a class.
//		- use of default constructor, parameterized constructor, and copy constructor.
//		- use of STL algorithms like sort.
//		- use of smart pointers for memory management.
//		- use of const and reference qualifiers for member functions.
//		- use of move semantics for transferring ownership of resources.
//
// The main function calls the Solution.run() function to execute the program.
//
// @note This program is part of a series of coding challenges and exercises.
// 
// @date 2023-14-05
#include <cmath>
#include <ctime>
#include <string>
#include <cstdio>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <memory>

using namespace std;

//	@brief A class that implements a text filter for filtering strings based on specific criteria.
//	@details The class provides methods to check if a string matches the filter criteria, reset the filter,	
//			 and check if the filter is active. The filter can be set to check for contains, starts with,
//			 or ends with a specific string. The filter is used to hide records in the EmailsDBTable class.
//	@note The filter is implemented using a simple string matching algorithm. The filter type is defined as an
//			enum class, and the filter criteria is stored as a string. The filter is active if the type is valid.
class TextFilter {
public:
	enum FilterType { ft_CONTAINS, ft_STARTS_WITH, ft_ENDS_WITH, ft_INVALID_FILTER_TYPE };
	TextFilter(FilterType type, const string& criteria)
		: type_(type), criteria_(criteria) {is_active_ = (type < ft_INVALID_FILTER_TYPE);}

	bool isActive() const {
		return is_active_;
	}

	void reset() {
		is_active_ = false;
	}

	bool matches(const string& text) const {
		switch (type_) {
			case ft_CONTAINS:
				return text.find(criteria_) != string::npos; break;
			case ft_STARTS_WITH:
				return text.rfind(criteria_, 0) == 0; break;
			case ft_ENDS_WITH:
				return ((text.size() >= criteria_.size()) &&
						(text.compare(text.size() - criteria_.size(), criteria_.size(), criteria_)) == 0); break;
			default:
				return false;
		}
	}

private:
	FilterType	type_;
	string 		criteria_;
	bool 		is_active_;
};


//	@brief A structure that represents a record in the email database.
//	@details The structure contains the first name, email ID, and a hidden flag to indicate if the record is hidden.	
//			 The structure provides a default constructor, a parameterized constructor, and a copy constructor.
//	@note The structure is used to store records in the EmailsDBTable structure. The hidden
//		 flag is used to filter records based on the filter criteria. The structure is used in the EmailsDBTable class.
//		 The structure is used to store records in the EmailsDBTable class. The hidden flag is used to filter records based on the filter criteria.
typedef struct PersonRecord
{
	string  first_name_;
	string  email_id_;
	bool    hidden_;

	PersonRecord() : first_name_(""), email_id_(""), hidden_(false) {} // Default constructor
	PersonRecord(string first_name, string email_id) : first_name_(first_name), email_id_(email_id), hidden_(false) {} // Parameterized constructor
	PersonRecord(const PersonRecord& other) : first_name_(other.first_name_), email_id_(other.email_id_), hidden_(other.hidden_) {} // Copy constructor
} PersonRecord;


// Sort Strategy Interface
class SortStrategy {
    public:
		enum SortOrder {so_ASC, so_DESC, so_UNDEFINED_SORT_ORDER};					//	Sort order
		enum SortCriteria {sc_BY_NAME, sc_BY_EMAIL, sc_UNDEFINED_SORT_CRITERIA};	//	Sort criteria

		virtual void execute(vector<PersonRecord>& records, SortOrder order) = 0; // Pure virtual function
		virtual ~SortStrategy() {} // Virtual destructor
};


// Concrete Sort Strategy for sorting by name in ascending order
class SortByName : public SortStrategy {
public:
    void execute(vector<PersonRecord>& records, SortOrder order) override {
        sort(records.begin(), records.end(), [order](const PersonRecord& lhs, const PersonRecord& rhs) {
            return ((order == SortOrder::so_ASC) ? (lhs.first_name_ < rhs.first_name_) : (lhs.first_name_ > rhs.first_name_));
        });
    }
};


// Concrete Sort Strategy for sorting by email in ascending order
class SortByEmail : public SortStrategy {
public:
	void execute(vector<PersonRecord>& records, SortOrder order) override {
		sort(records.begin(), records.end(), [order](const PersonRecord& lhs, const PersonRecord& rhs) {
			return (order == SortOrder::so_ASC) ? lhs.email_id_ < rhs.email_id_ : lhs.email_id_ > rhs.email_id_;
		});
	}
};


//	@brief A class that represents an email database table.
//	@details The class contains a collection of email records, a filter for filtering records, and a sort strategy
//			 for sorting records. The class provides methods to filter records by email and name, reset the filter,
//			 set the sort strategy, execute the sort, and dump records based on the specified criteria.
class EmailsDBTable
{
	friend istream& getARecordFromConsole(istream &input, EmailsDBTable& obj);
	private:
		vector <PersonRecord> 		record_collection_;		// Collection of records
        unique_ptr<SortStrategy>	sortStrategy_;	// Sort Strategy
		TextFilter 					filter_;			// Filter for email records

    public:
		enum dumpCriteria {dc_NAME, dc_EMAIL, dc_ALL};	//	criteria for dump

		EmailsDBTable() : filter_(TextFilter::ft_INVALID_FILTER_TYPE, "") {}

        void filterByEmail(const TextFilter& filter) {
            filter_ = filter;
            for (auto& record : record_collection_) {
                if (!filter_.matches(record.email_id_)) {
                    record.hidden_ = true;
                }
            }
        }

        void filterByName(const TextFilter& filter) {
            filter_ = filter;
            for (auto& record : record_collection_) {
                if (!filter_.matches(record.first_name_)) {
                    record.hidden_ = true;
                }
            }
        }

		void filterReset() {
			for (auto& record : record_collection_) {
				record.hidden_ = false;
			}
			filter_.reset(); // Reset the filter status
		}

		bool isFilterActive() {
			return filter_.isActive(); // Check if the filter is active
		}
        
        void setSortStrategy(unique_ptr<SortStrategy> strategy) {
            sortStrategy_ = move(strategy);
        }

        void executeSort(SortStrategy::SortOrder order) {
            if (sortStrategy_) {
                sortStrategy_->execute(record_collection_, order);
            } else {
                cout << "No sort strategy set" << endl;
            }
        }

		void getInputsFromConsole()
		{
			int capacity;
			cin >> capacity;
			this->setCapacity(capacity);

			for(int i=0; i<capacity; ++i)
			{
				getARecordFromConsole(cin, *this);
			}
			this->filterReset(); // Reset the filter status
		}

		void setCapacity(int value) { record_collection_.reserve(value); };
		int getCapacity() { return record_collection_.size(); };
		void pushARecord(PersonRecord* item) { record_collection_.push_back(*item); };
		int dumpRecords(dumpCriteria criteria);
};


// Dumps the email records based on the specified criteria and filter.
//
// @param criteria The criteria for dumping the records. It can be one of the following:
//                 - dc_NAME: Dump only the names.
//                 - dc_EMAIL: Dump only the email IDs.
//                 - dc_ALL: Dump both names and email IDs.
// @return Returns 0 on success, or -1 if an invalid criteria is provided
int
EmailsDBTable::dumpRecords(dumpCriteria criteria)
{
	int result = 0;

	for (int i=0; i<record_collection_.size(); ++i) {
		if(isFilterActive() && record_collection_[i].hidden_)
			continue;
		else{
			if(criteria == dc_NAME)
				cout << record_collection_[i].first_name_ << endl;
			else if(criteria == dc_EMAIL)
				cout << record_collection_[i].email_id_ << endl;
			else if(criteria == dc_ALL)
				cout << record_collection_[i].first_name_ << " " << record_collection_[i].email_id_ << endl;
			else
				result = -1;
		}
	}

	return result;
}


// @brief Extracts a record from the input stream and adds it to the emails database.
//
// This function reads a first name and an email ID from the input stream, creates
// a record with these values, sets the hidden flag to false, and then pushARecordes the
// record into the provided emails database.
//
// @param input The input stream to read from.
// @param obj The emails database to which the record will be added.
// @return The input stream after extraction.
istream& getARecordFromConsole(istream &input, EmailsDBTable& obj)
{
	PersonRecord record;

	input >> record.first_name_ >> record.email_id_;
	record.hidden_ = false;
	obj.pushARecord(&record);

	return input;
}

//	@brief A class that implements the solution for the email database problem.
//	@details The class contains a method to run the solution, which includes creating an instance of the
//			 EmailsDBTable class, getting inputs from the console, filtering records by email, setting the sort strategy,	
//			 executing the sort, and dumping records based on the specified criteria.
//	@note The class is used to encapsulate the solution and provide a clean interface for running the program.
class Solution {
public:
	void run()
	{
		EmailsDBTable myDB;

		myDB.getInputsFromConsole();
		myDB.filterByEmail(TextFilter(TextFilter::ft_ENDS_WITH, "@gmail.com"));
		myDB.setSortStrategy(make_unique<SortByName>());
		myDB.executeSort(SortStrategy::so_ASC);
		myDB.dumpRecords(EmailsDBTable::dc_NAME);
	}
};


/*-------------------------------------------------------------------*/
// @brief The main function that runs the program.
/*-------------------------------------------------------------------*/
int main(){
    Solution solution;
	solution.run();

    return 0;
}
