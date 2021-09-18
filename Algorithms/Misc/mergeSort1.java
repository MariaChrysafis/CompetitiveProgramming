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
    int n, k;
    cin >> n >> k;
    if(n == k) {
        for(int i = 0; i < n; i++ ) cout << 0;
        return;
    }
    if(k == 1) {
        cout << 1;
        for(int i = 0; i < n - 1; i++) cout << 0;
        return;
    }
    for(int i = 0; i < n; i++) {
        cout << (i % ((n - k)/2 + 1) == (n - k)/2);
    }

}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
}
