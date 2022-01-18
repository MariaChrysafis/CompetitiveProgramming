#include <vector>
#include <chrono>
#include <iostream>
#include <map>
#include <set>
#include <climits>
#include <cmath>
#include <cassert>
#include <iomanip>
#include <stack>
#include <unordered_map>
#include <queue>
#include <algorithm>
#include <string>

using namespace std;

typedef int64_t ll;

string ts (char c) {
    string s = " ";
    s[0] = c;
    return s;
}

int to_int (string s) {
    int ans = 0;
    for (int i = 0; i < s.length(); i++) {
        ans += pow(10, s.length() - i - 1) * (s[i] - '0');
    }
    return ans;
}

int time (string s) {
    s.pop_back();
    reverse(s.begin(), s.end());
    s.pop_back();
    reverse(s.begin(), s.end());
    string year = ts(s[0]) + s[1] + s[2] + s[3];
    string month = ts(s[5]) + s[6];
    string day = ts(s[8]) + s[9];
    string hour = ts(s[11]) + s[12];
    string minute = ts(s[14]) + s[15];
    int days = to_int(year) * 365 + to_int(month) * 12 + to_int(day);
    days *= 24 * 60;
    days += to_int(hour) * 60;
    days += to_int(minute);
    return days;
}

bool comp (vector<string> v1, vector<string> v2) {
    return (time(v1[0] + " " + v1[1]) < time(v2[0] + " " + v2[1]));
}

int main() {
    const int T = 1151;
    map<int,vector<pair<int,int>>> intervals;
    vector<vector<string>> vec;
    for (int tc = 1; tc <= T; tc++) {
        string s1, s2;
        cin >> s1 >> s2;
        string dum;
        cin >> dum;
        //cout << s1 << " " << s2 << " " << dum << '\n';
        if (dum == "Guard") {
            string num;
            cin >> num;
            reverse(num.begin(), num.end()), num.pop_back(), reverse(num.begin(), num.end());
            vec.push_back({{s1, s2, dum, num}});
            cin >> dum >> dum;
        } else if (dum == "wakes") {
            vec.push_back({s1, s2, dum});
            cin >> dum;
        } else {
            vec.push_back({s1, s2, dum});
            cin >> dum;
        }
    }
    sort(vec.begin(), vec.end(), comp);
    //return 0;
    int curGuard = -1;
    string status = "asleep";
    int curTime = 0;
    for(auto& p: vec) {
        string s1 = p[0];
        string s2 = p[1];
        int tm = time(s1 + " " + s2);
        string dum = p[2];
        cout << s1 << " " << s2 << " " << dum << '\n';
        assert(curTime <= tm);
        if (dum == "Guard") {
            string num = p[3];
            curGuard = to_int(num);
            status = "asleep";
            curTime = tm;
        } else if (dum == "wakes") {
            if (status == "asleep") {
                intervals[curGuard].push_back({curTime, tm});
                status = "awake";
                curTime = tm;
            }
        } else if (dum == "falls") {
            if (dum == "wakes") {
                status = "asleep";
                curTime = tm;
            }
        }
    }
    int best = -1;
    int best_time = -1;
    vector<int> boc(60);
    for (auto& p: intervals) {
        int t = 0;
        vector<int> oc(60);
        for (auto& q: intervals[p.first]) {
            t += q.second - q.first;
            for (int k = q.first; k <= q.second; k++) {
                oc[k % 60]++;
            }
        }
        if (t > best_time) {
            best_time = t;
            best = p.first;
            boc = oc;
        }
    }
    cout << best << '\n';
    best = 0;
    best_time = 0;
    for (int i = 0; i < boc.size(); i++) {
        if (boc[i] > best_time) {
            best_time = boc[i];
            best = i;
        }
    }
    cout << best << '\n';
}
