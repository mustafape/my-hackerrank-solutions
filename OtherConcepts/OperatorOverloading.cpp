#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class Matrix {
    public:
        vector <vector<int>> a;

        friend Matrix operator+ (const Matrix& first, const Matrix& second) {
            Matrix* result = new Matrix();

            for(unsigned int row=0; row<first.a.size(); ++row) {
                vector<int> a_row;
                for(unsigned int col=0; col<first.a[row].size(); ++col) {
                    a_row.push_back(first.a[row][col]+second.a[row][col]);
                }
                result->a.push_back(a_row);
            }

            return *result;
        };
};

int main () {
   int cases,k;
   cin >> cases;
   for(k=0;k<cases;k++) {
      Matrix x;
      Matrix y;
      Matrix result;
      int n,m,i,j;
      cin >> n >> m;
      for(i=0;i<n;i++) {
         vector<int> b;
         int num;
         for(j=0;j<m;j++) {
            cin >> num;
            b.push_back(num);
         }
         x.a.push_back(b);
      }
      for(i=0;i<n;i++) {
         vector<int> b;
         int num;
         for(j=0;j<m;j++) {
            cin >> num;
            b.push_back(num);
         }
         y.a.push_back(b);
      }
      result = x+y;
      for(i=0;i<n;i++) {
         for(j=0;j<m;j++) {
            cout << result.a[i][j] << " ";
         }
         cout << endl;
      }
   }  
   return 0;
}

