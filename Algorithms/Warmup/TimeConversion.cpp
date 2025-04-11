#include <bits/stdc++.h>

using namespace std;

/*
 * Complete the 'timeConversion' function below.
 *
 * The function is expected to return a STRING.
 * The function accepts STRING s as parameter.
 */

void stringToTokens(string s, char delimiter, vector<string> * tokens)
{
    stringstream check(s);
    string part;
    
    while(getline(check, part, ':'))
    {
        tokens->push_back(part);
    }
}

string timeConversion(string s) {

    // initialize and allocate string to return
    string result = string("hh:mm:ss");

    // find if AM/PM    
    bool is_am = (bool)(string(s.end()-2, s.end()).compare("AM") == 0);

    // drop AM/PM part
    s = string(s.begin(), s.end()-2);

    // get sub-streams
    vector<string> tokens;
    stringToTokens(s, ':', &tokens);

    // get hh, mm, ss
    int hh = stoi(tokens[0]);
    int mm = stoi(tokens[1]);
    int ss = stoi(tokens[2]);

    // fix AM/PM to 24 hour format
    hh =(is_am) ? ((hh == 12) ? hh=0:hh) : ((hh!=12) ? hh+12:hh);

    // construct result string
    sprintf((char*)result.c_str(), "%02d:%02d:%02d", hh, mm, ss);

    return result;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string s;
    getline(cin, s);

    string result = timeConversion(s);

    fout << result << "\n";

    fout.close();

    return 0;
}
