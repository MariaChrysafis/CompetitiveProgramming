#include <iostream>
#include <vector>
#include <map>
#include <cassert>
#include <set>
#include <unordered_set>
#include <algorithm>
#include <random>
#include <chrono>
#include <queue>
#include <array>
 
#define ll long long
#define endl '\n'
 
using namespace std;
ll res(ll a, ll b, ll c){
    return a * (a - 1)/2 * (c + 1) + b * (b - 1)/2 + a * b;
}
ll binSearch(ll l, ll r, ll b, ll c, ll des){
    ll m = (l + r)/2;
    if(l == r){
        if (res(l, b, c) != des) return -1;
        return l;
    }
    if(res(m, b, c) >= des){
        return binSearch(l, m, b, c, des);
    }else{
        return binSearch(m + 1, r, b, c, des);
    }
}
void solve() {
    long long n;
    cin >> n;
    ll x = sqrt(n) + 3;
    for(int i = x; i >= 0; i--){
        for(int c = 0; c <= 50; c++) {
            int x = binSearch(0, (long long) 1e4, i, c, n);
            if (x == -1) {
                continue;
            }
            cout << 1;
            for (int j = 0; j < x; j++) cout << 3;
            for(int j = 0; j < c; j++) cout << 7;
            for (int j = 0; j < i; j++) cout << 3;
            cout << 7;
            cout << endl;
            return;
        }
    }
    for(int i = x; i >= 0; i--){
        for(int c = 51; c <= 150; c++) {
            int x = binSearch(0, (long long) 1e4, i, c, n);
            if (x == -1) {
                continue;
            }
            cout << 1;
            for (int j = 0; j < x; j++) cout << 3;
            for(int j = 0; j < c; j++) cout << 7;
            for (int j = 0; j < i; j++) cout << 3;
            cout << 7;
            cout << endl;
            return;
        }
    }
    for(int i = x; i >= 0; i--){
        for(int c = 151; c <= 161; c++) {
            int x = binSearch(0, (long long) 1e4, i, c, n);
            if (x == -1) {
                continue;
            }
            cout << 1;
            for (int j = 0; j < x; j++) cout << 3;
            for(int j = 0; j < c; j++) cout << 7;
            for (int j = 0; j < i; j++) cout << 3;
            cout << 7;
            cout << endl;
            return;
        }
    }
    cout << "-1\n";
}
 
int main() {
    int t;
    cin >> t;
    while(t--){
        solve();
    }
}
