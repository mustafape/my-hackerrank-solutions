#include <iostream>
#include <vector>

using namespace std;


class Person{
	protected:
		string firstName;
		string lastName;
		int id;
	public:
		Person(string firstName, string lastName, int identification){
			this->firstName = firstName;
			this->lastName = lastName;
			this->id = identification;
		}
		void printPerson(){
			cout<< "Name: "<< lastName << ", "<< firstName <<"\nID: "<< id << "\n"; 
		}
	
};

class Student :  public Person{
	private:
		vector<int> testScores;  
	public:
        /*	
        *   Class Constructor
        *   
        *   Parameters:
        *   firstName - A string denoting the Person's first name.
        *   lastName - A string denoting the Person's last name.
        *   id - An integer denoting the Person's ID number.
        *   scores - An array of integers denoting the Person's test scores.
        */
        // Write your constructor here

        /*	
        *   Function Name: calculate
        *   Return: A character denoting the grade.
        */
        // Write your function here
        Student(string firstName, string lastName, int id, vector<int> scores)
            : Person(firstName, lastName, id)
        {
            for(unsigned int i=0; i<scores.size(); ++i)
                testScores.push_back(scores[i]);
            
            formatChecker();
        }

		string getFirstName() { return firstName; };
		string getLastName() { return lastName; };

        char calculate()
        {
            int total = 0, average = 0;
            char grade_letter='T';

            if(testScores.size())
            {
                for(unsigned int i=0; i< testScores.size(); ++i)
                {
                    total += testScores[i];
                }

                average = total / testScores.size();

                if(average >= 90 && average <= 100)
                {
                    grade_letter = 'O';
                }
                else if(average >= 80 && average < 90)
                {
                    grade_letter = 'E';
                }
                else if(average >= 70 && average < 80)
                {
                    grade_letter = 'A';
                }
                else if(average >= 55 && average < 70)
                {
                    grade_letter = 'P';
                }
                else if(average >= 40 && average < 55)
                {
                    grade_letter = 'D';
                }
                else if(average < 40)
                {
                    grade_letter = 'T';
                }
            }

            return grade_letter;
        }

        void formatChecker() { }
};

int main() {
	string firstName;
  	string lastName;
	int id;
  	int numScores;
	cin >> firstName >> lastName >> id >> numScores;
  	vector<int> scores;
  	for(int i = 0; i < numScores; i++){
	  	int tmpScore;
	  	cin >> tmpScore;
		scores.push_back(tmpScore);
	}
	Student* s = new Student(firstName, lastName, id, scores);
	s->printPerson();
	cout << "Grade: " << s->calculate() << "\n";
	return 0;
}