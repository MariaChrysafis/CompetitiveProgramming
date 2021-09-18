#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <map>
#include <set>
#include <iomanip>
#include <algorithm>
#include <queue>

#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
using namespace std;

template<typename T>
T readVal() {
    T n;
    cin >> n;
    return n;
}

template<typename T>
vector<T> readVector(int n) {
    vector<T> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }
    return v;
}

template<typename T>
void printVector(vector<T> vec) {
    for (T x: vec) {
        cout << x << " ";
    }
    cout << endl;
}

template<typename T>
void printVectorVector(vector<vector<T>> vec) {
    for (vector<T> x: vec) {
        //cout << x << " ";
        printVector(x);
    }
    cout << endl;
}

long long powr(long long x) {
    long long cur = 1;
    while (x--) {
        cur *= 2;
    }
    return cur;
}

string to_string(char c) {
    string s = "";
    s += c;
    return s;
}

string sorted(string s) {
    sort(s.begin(), s.end());
    return s;
}

void solve() {
    int n;
    cin >> n;
    vector<vector<int>> adj(n);
    vector<vector<int>> rev_adj(n);
    for(int i = 0; i < n; i++) {
        int k;
        cin >> k;
        for(int j = 0; j < k; j++) {
            int x;
            cin >> x;
            x--;
            adj[x].push_back(i);
            rev_adj[i].push_back(x);
        }
    }

    set<int> q;
    vector<int> inDeg(n);
    for(int i = 0; i < n; i++) {
        inDeg[i] = rev_adj[i].size();
        if(inDeg[i] == 0) {
            q.insert(i);
        }
    }
    int prev = 0;
    int cntr = 1;
    vector<int> ans;
    while(!q.empty()) {
        int x;
        if(q.lower_bound(prev) != q.end()) {
            x = *q.lower_bound(prev);
        } else {
            x = *q.begin();
            cntr++;
        }
        ans.push_back(x);
        q.erase(x);
        prev = x;
        for(int i: adj[x]) {
            inDeg[i]--;
            if(inDeg[i] == 0) {
                q.insert(i);
            }
        }
    }
    vector<int> dum;
    for(int i = 0; i < n; i++){
        dum.push_back(i);
    }
    sort(ans.begin(), ans.end());
    if(dum != ans) {
        cout << -1 << '\n';
        return;
    }
    cout << cntr << '\n';
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while(t--) {
        solve();
    }
}

/*
 * Segment/Fenwick/Binary Index Tree? For backtracking? For dynamic programming?
 * Simplify the problem
 * Dynamic programming? Bitwise DP? What are teh states we need? Two row optimization?
 * Combinatorics: mostly DP, usually, but try to use some binomial magic
 * [][] int arr[]; vector<int> v
 */
