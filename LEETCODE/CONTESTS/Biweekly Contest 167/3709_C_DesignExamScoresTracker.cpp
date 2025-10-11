#include <bits/stdc++.h>
using namespace std;
class ExamTracker {
public:
    vector<int>a;
    vector<long long>f;
    ExamTracker() {
        
    }
    int l_b(vector<int>&a, int x){
        int low = 0; 
        int high = a.size()-1;
        int ans = -1;
        while(low <= high){
            int mid = low + (high - low) / 2;
            if(a[mid] <= x){
                ans = mid;
                low = mid + 1;
            }else high = mid - 1;
        }
        return ans;
    }
    void record(int time, int score) {
        a.push_back(time);
        if(f.empty()) f.push_back(score);
        else f.push_back(f.back() + score);
    }
    
    long long totalScore(int startTime, int endTime) {
        if(a.empty()) return 0;
        int lb_s = l_b(a,startTime-1);
        int lb_e = l_b(a, endTime);

        if(lb_e == -1) return 0;
        if(lb_s == -1) return f[lb_e];
        
        return f[lb_e] - f[lb_s];
    }
};

/**
 * Your ExamTracker object will be instantiated and called as such:
 * ExamTracker* obj = new ExamTracker();
 * obj->record(time,score);
 * long long param_2 = obj->totalScore(startTime,endTime);
 */