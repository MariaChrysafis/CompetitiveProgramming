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

string to_string(char c){
    string s = "";
    s += c;
    return s;
}

string sorted(string s){
    sort(s.begin(), s.end());
    return s;
}

void solve() {
    int n;
    cin >> n;
    string s1, s2;
    cin >> s1 >> s2;
    if(sorted(s1) != sorted(s2)){
        cout << "-1";
        return;
    }
    int myMax = 0;
    int cntr = 0;
    for(char c = '0'; c <= '1'; c++) {
        for (int i = 0; i < s1.length(); i++) {
            if (s1[i] == s2[i]) continue;
            cntr += 2 * (s1[i] == c) - 1;
            if (cntr < 0) cntr = 0;
            myMax = max(myMax, cntr);
        }
        cntr = 0;
    }
    cout << myMax << endl;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
}
