#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
/*-------------------------------------------------------------------*/
//	Virtual Functions
/*-------------------------------------------------------------------*/
class Person
{
	public:
		Person(string name, int age)
		: m_name(name),
   		  m_age(age)
		{
		};

		~Person(){};

		virtual void getdata() = 0;
		virtual void putdata() = 0;

	protected:
		string m_name;
        int m_uid;	// this will be printed id
		int m_age;
};

class Student : public Person
{
	public:	
		Student() 
			: Person("", 0)
		{
			m_uid = ++m_id;
		}

		~Student();

	virtual void getdata()
	{
		cin >> m_name >> m_age;
		for(int i=0; i<6; ++i)
		{
			cin >> m_marks[i];
		}
	}
	
	virtual void putdata()
	{
		int total = 0;
		cout << m_name << " " << m_age << " ";
		for(int i=0; i<6; ++i)
		{
			total += m_marks[i];
		}

		cout << total << " " << m_uid << endl;
	}

	private: 
		static int m_id;	// will be used for calculating id.
		int m_marks[6];
};

int Student::m_id = 0;

class Professor : public Person
{
	public:	
		Professor() 
			: Person("", 0)
		{
			m_uid = ++m_id;
		}

		~Professor();

		virtual void getdata()
		{
			cin >> m_name >> m_age >> m_publications;
		}
		
		virtual void putdata()
		{
			cout << m_name << " " << m_age << " " << m_publications << " " << m_uid << endl;
		}

	private: 
		static int m_id;	// will be used for calculating id.

		int m_publications;
};

int Professor::m_id = 0;



int main(){

    int n, val;
    cin>>n; //The number of objects that is going to be created.
    Person *per[n];

    for(int i = 0;i < n;i++){

        cin>>val;
        if(val == 1){
            // If val is 1 current object is of type Professor
            per[i] = new Professor;

        }
        else per[i] = new Student; // Else the current object is of type Student

        per[i]->getdata(); // Get the data from the user.

    }

    for(int i=0;i<n;i++)
        per[i]->putdata(); // Print the required output for each object.

    return 0;

}
