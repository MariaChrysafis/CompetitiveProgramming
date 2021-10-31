#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_set>
#include <set>
#include <unordered_map>
#include <map>
#define ll signed long long
#pragma GCC optimize("Ofast")
using namespace std;
vector <ll> p;
void solve() {
    ll n, k;
    cin >> n >> k;
    if (n == 1) {
        cout << 0 << endl;
        return;
    }
    ll computers = 1;
    ll chords = 1;
    ll day = 1;
    while(true) {
        computers += chords;
        chords *= 2;
        if (chords >= k) {
            chords = k;
            break;
        }
        if (computers >= n) {
            cout << day << endl;
            return;
        }
        day++;
    }
    cout << (n - computers + k - 1)/k + day << endl;
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
