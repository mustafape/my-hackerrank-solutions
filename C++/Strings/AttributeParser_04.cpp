#include <iostream>
#include <sstream>
#include <map>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>
#include <iterator>
#include <cctype>
#include <cstdlib>
#include <cstdio>
using namespace std;

// Link: https://www.hackerrank.com/challenges/attribute-parser/problem

class Solution {
private:
    vector<string>      m_HRMLList;
    vector<string>      m_Queries;
    vector<string>      m_TagList;
    map<string, string> m_AttributeValues ;
public:
    ~Solution() {
        m_HRMLList.clear();
        m_Queries.clear();
        m_TagList.clear();
        m_AttributeValues.clear();
    }

    Solution() {
        m_HRMLList.clear();
        m_Queries.clear();
        m_TagList.clear();
        m_AttributeValues.clear();
    }
    
    //=======================================================================
    // This function processes the queries and prints the attribute values
    // It uses the m_AttributeValues map to find the attribute values based on the queries
    // It prints the attribute value if found, otherwise it prints "Not Found!"
    //=======================================================================
    void processQueries() {
        for (const auto &query : m_Queries) {
            auto it = m_AttributeValues.find(query);
            if (it != m_AttributeValues.end()) {
                cout << it->second << endl;
            } else {
                cout << "Not Found!" << endl;
            }
        }
    }

    //=======================================================================
    // This function returns the tag name by concatenating the tags in the m_TagList vector 
    //=======================================================================
    string getTagName() {
        string tagName = m_TagList[0];

        for (int i = 1; i < m_TagList.size(); ++i) {
            tagName += "." + m_TagList[i];
        }

        return tagName;
    }

    //=======================================================================
    // This function processes the tokens and extracts the tag name and attributes
    // It uses a stack-like approach to keep track of the current tag context
    // It assumes that the very first token is the tag name, 
    // Next tokens are attribute name, equal sign, and attribute value
    // It also assumes that the attribute value is enclosed in double quotes
    //=======================================================================
    void processTokens(const vector<string> &tokens) {    
        if(tokens.size() == 0) return; // No tokens to process

        string tagName, attrName, attrValue, equalSign;
        int tokenIndex = 0;

        tagName = tokens[tokenIndex++];    // Assuming the 1st token is the tag name
        
        if(tagName[0] == '/') { // If the first token is a closing tag
            m_TagList.pop_back(); // Remove the last tag from the list
        }
        else {  // If the first token is an opening tag
            m_TagList.push_back(tagName); // Add the tag to the list
        }

        //tokens.erase(tokens.begin()); // Remove the processed token

        while(tokenIndex < tokens.size()) {  // Process the remaining tokens
            attrName  = tokens[tokenIndex++]; // Assuming the next token is the attribute name
            equalSign = tokens[tokenIndex++]; // Assuming the next token is the equal sign
            attrValue = tokens[tokenIndex++]; // Assuming the next token is the attribute value
            attrValue = attrValue.substr(1, attrValue.size() - 2); // Remove " and " from the attribute value

            //tokens.erase(tokens.begin(), tokens.begin() + 3);  // Remove the processed tokens

            m_AttributeValues[getTagName() + "~" + attrName] = attrValue;   // Store the attribute value in the map
        }
    }

    //=======================================================================
    // This function processes the HRML list and extracts the tags and attributes
    // It uses a stack-like approach to keep track of the current tag context
    void processHRMLList() {
        for (const auto &line : m_HRMLList) {
            processTokens(getTokens(line));
        }
    }

    //=======================================================================
    // This function;
    // - removes the '<' and '>' from the line
    // - used to split the line into tokens based on the delimiter (default is space)
    //=======================================================================
    vector <string> getTokens(const string &line, char delimiter = ' ') {
        vector<string> tokenVector;
        string refined_line = line.substr(1, line.size() - 2); // Remove '<' and '>'
        istringstream hasTokens(refined_line);

        while(hasTokens)
        {
            string token;
            if(getline(hasTokens, token, delimiter))
                tokenVector.push_back(token);
        }
        
        return tokenVector;
    }

    //=======================================================================
    // Function to get the number of lines from the console
    //=======================================================================
    vector<string> getNumOfLines(int n) {
        vector<string> lines;
        string line;
        for (int i = 0; i < n; ++i) {
            getline(cin, line);
            lines.push_back(line); // Refine the line if needed
        }
        return lines;
    }

    //=======================================================================
    // Function to get entries from the console
    // This function reads the number of lines in HRML and number of queries
    //=======================================================================
    void getEntriesFromConsole() {
            int numLinesInHRML, numQueries;
            string line;

            // Read the first line to get the number of lines in HRML and number of queries
            getline(cin, line);
            istringstream iss(line);

            // get the number of lines in HRML and number of queries
            iss >> numLinesInHRML >> numQueries;

            // Read the HRML lines and queries from the console
            m_HRMLList = getNumOfLines(numLinesInHRML);
            m_Queries = getNumOfLines(numQueries);
    }

    //=======================================================================
    // Main function to run the solution
    //=======================================================================
    void runSolution() {
        getEntriesFromConsole();
        processHRMLList();
        processQueries();
    }

    //=======================================================================
    // Helper functions to print the vectors and maps for debugging purposes
    //=======================================================================
    void printTagList(void) {
        cout << "Tag List:" << endl;
        for (const auto &tag : m_TagList) {
            cout << tag << endl;
        }
    }
    void printVector(const vector<string> &vec) {
        for (const auto &str : vec) {
            cout << str << endl;
        }
    }
    void printHRMLList(void) { printVector(m_HRMLList); }
    void printQueries(void) { printVector(m_Queries); }

    void printAttributeValues() {
        cout << "Attribute Map:" << endl;

        for (auto it=m_AttributeValues.rbegin(); it!=m_AttributeValues.rend(); ++it) {
            cout << it->first << " = " << it->second << endl;
        }
    }
    //=======================================================================
    // End of helper functions
    //=======================================================================
};

int main() {
    
    Solution solution;
    solution.runSolution();

    return 0;
}