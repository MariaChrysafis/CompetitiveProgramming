#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <cassert>
#include <map>
#include <complex>
#include <cmath>
#include <stdio.h>
#include <string.h>
#include <set>
#include <queue>
#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops"
using namespace std;
int solve (vector<int>&s, vector<int>& v) {
    if (s.empty()) return 0;
    int64_t ending = s.back();
    int64_t beginning = s[0];
    int64_t myMin = INT_MAX;
    for (int i = 1; i < v.size(); i++) {
        myMin = min(myMin, abs(v[i] - beginning) + abs(ending - v[i - 1]) - abs(v[i - 1] - v[i]));
        myMin = min(myMin, abs(v[i] - ending) + abs(v[i - 1] - beginning) - abs(v[i - 1] - v[i]));
    }
    myMin = min(myMin, abs(ending - v.back()));
    myMin = min(myMin, abs(beginning - v.back()));
    myMin = min(myMin, abs(ending - v[0]));
    myMin = min(myMin, abs(beginning - v[0]));
    return myMin;
}
vector<vector<int>> split (vector<int> &v) {
    vector<vector<int>> vec;
    vec.emplace_back();
    vec.back().push_back(v[0]);
    for (int i = 1; i < v.size(); i++) {
        if (vec.back().back() + 1 == v[i]) {
            vec.back().push_back(v[i]);
        } else {
            vec.emplace_back();
            vec.back().push_back(v[i]);
        }
    }
    return vec;
}
int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        int64_t n, x;
        cin >> n >> x;
        vector<int> v(n);
        int myMin = INT_MAX, myMax = 0;
        for (int i = 0; i < n; i++) {
            cin >> v[i];
            myMin = min(myMin, v[i]);
            myMax = max(myMax, v[i]);
        }
        int64_t ans = 0;
        for (int i = 1; i < n; i++) {
            ans += abs(v[i] - v[i - 1]);
        }
        vector<int> my;
        if (myMin > x) {
            for (int i = 1; i <= x; i++) {
                my.push_back(i);
            }
            ans += solve(my, v);
            ans += my.back() - my[ 0];
        } else {
            for (int i = 1; i < myMin; i++) {
                my.push_back(i);
            }
            if (!my.empty()) {
                ans += abs(my.back() - my[0]);
            }
            ans += solve(my, v);
            my.clear();
            for (int i = myMax + 1; i <= x; i++) {
                my.push_back(i);
            }
            if (!my.empty()) {
                ans += abs(my.back() - my[0]);
            }
            ans += solve(my, v);
        }
        cout << ans << '\n';
    }
}
