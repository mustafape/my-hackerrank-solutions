#include<bits/stdc++.h>
#include<vector>

using namespace std;

//Define the structs Workshops and Available_Workshops.
//Implement the functions initialize and CalculateMaxWorkshops
struct Workshop {
    int start_time;
    int duration;
    int end_time;
    
    Workshop()
    : start_time(0), end_time(0), duration(0) {}

    Workshop(int s, int d)
    : start_time(s), duration(d) { end_time = start_time + duration; }
    
    void setWorkshop(int s, int d) {
        start_time = s;
        duration = d;
        end_time = start_time + duration;
    }
    
    bool Conflicts(Workshop w) {
        if((this->start_time <= w.start_time) && (this->end_time >= w.start_time))
            return true;

        else if((w.start_time <= this->start_time) && (w.end_time >= this->start_time))
            return true;
            
        return false;
    }
};

struct Available_Workshops {
    int n;
    Workshop* pw;

    Available_Workshops(int* st, int* d, int nn) {
        n = nn;
        pw = new Workshop[nn];        

        for(int i=0; i<nn; ++i)
        {
            pw[i].setWorkshop(*st++, *d++);
        }
    }
};

Available_Workshops* initialize (int * start_time, int * duration, int n) {
    Available_Workshops* result = new Available_Workshops(start_time, duration, n);
    
    return result;
}

int CalculateMaxWorkshops(Available_Workshops * ptr) {
    vector<Workshop> w;
    
    for(auto i=0; i< ptr->n; ++i) {
        w.push_back(ptr->pw[i]);
    }

    sort(w.begin(), w.end(), [](const Workshop& a, const Workshop& b) { return a.end_time < b.end_time;});
    
    int result = 0;
    int f = 0;
    for(int i = 0; i < w.size(); i++) {
        if(w[i].start_time >= f){
            result++;
            f = w[i].end_time;
        }
    }

    return result;
}

int main(int argc, char *argv[]) {
    int n; // number of workshops
    cin >> n;
    // create arrays of unknown size n
    int* start_time = new int[n];
    int* duration = new int[n];

    for(int i=0; i < n; i++){
        cin >> start_time[i];
    }
    for(int i = 0; i < n; i++){
        cin >> duration[i];
    }

    Available_Workshops * ptr;
    ptr = initialize(start_time,duration, n);
    cout << CalculateMaxWorkshops(ptr) << endl;
    return 0;
}
