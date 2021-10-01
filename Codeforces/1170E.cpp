#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <algorithm>
#include <cmath>
#include <fstream>
#define ll long long

using namespace std;

vector<int> v, pref;

int find_sum (int l, int r) {
    if(l == 0) {
        return pref[r];
    }
    return pref[r] - pref[l - 1];
}

int binSearch(int left, int gap, int l, int r) {
    int m = (l + r + 1) >> 1;
    if(l == r) {
        return l;
    }
    if(find_sum (left, m) <= gap) {
        return binSearch(left, gap, m, r);
    } else {
        return binSearch(left, gap, l, m - 1);
    }
}

void solve() {
    int n, m;
    cin >> n >> m;
    v.resize(n);
    for(int i = 0; i < n; i++) {
        cin >> v[i];
    }
    pref.push_back(v[0]);
    for(int i = 1; i < n; i++) {
        pref.push_back(pref.back() + v[i]);
    }
    int q;
    cin >> q;
    while (q--) {
        int c;
        cin >> c;
        vector<int> employees(c);
        for(int i = 0; i < c; i++) {
            cin >> employees[i];
            employees[i]--;
        }
        vector<int> gaps;
        gaps.push_back(employees[0]);
        if(gaps.back() <= 0) gaps.pop_back();
        for(int i = 1; i < c; i++) {
            gaps.push_back(employees[i] - employees[i - 1] - 1);
            if(gaps.back() <= 0) gaps.pop_back();
        }
        gaps.push_back(m - 1 - employees.back());
        if(gaps.back() <= 0) gaps.pop_back();
        int cur = 0;
        for(int i = 0; i < gaps.size(); i++) {
            if(v[cur] > gaps[i]) {
                continue;
            }
            int x = binSearch(cur, gaps[i], cur, (int)v.size() - 1);
            cur = x + 1;
            if(cur == v.size()) break;
        }
        if(cur == v.size()) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
}
