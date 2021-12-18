#include <algorithm>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <random>
#include <set>
#include <stack>
#include <vector>
#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
typedef long long ll;

using namespace std;
int rec12 (set<int> s) {
    if (s.count(0)) s.erase(0);
    if (s.empty()) return 0;
    //we can only use 1s and 2s
    auto it = s.end(); it--;
    int need = 0;
    for (int i: s) {
        if (i % 2 == 1) {
            need = 1;
        }
    }
    return (*it)/2 + need;
}
int rec123 (set<int> s) {
    auto it = s.end(); it--;
    int largest = *it;
    int myMin = 1e9;
    for (int i = max(largest/3 - 1, 0); i <= largest/3; i++) {
        set<int> new_s;
        for (int el: s) {
            if (el - i * 3 < 0) new_s.insert(el % 3);
            else new_s.insert(el - i * 3);
        }
        myMin = min(myMin, i + rec12(new_s));
        if (new_s.count(1) && i != 0 && !s.count(1)) {
            new_s.erase(1);
            new_s.insert(4);
            myMin = min(myMin, i + rec12(new_s));
        }
    }
    return myMin;
}
void solve() {
    int n;
    cin >> n;
    vector<ll> arr(n); set<int> s;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        s.insert(arr[i]);
    }
    //cout << rec12({4, 2}) << '\n';
    cout << rec123(s) << '\n';
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}
