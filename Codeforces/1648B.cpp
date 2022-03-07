#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <cmath>
#include <map>
#include <random>
#include <ctime>
#include <cstdlib>
#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")

using namespace std;
bool contains (vector<int64_t>&pref, int64_t l, int64_t r) {
    return (pref[r + 1] - pref[l] >= 1);
}
void solve () {
    int64_t n, c;
    cin >> n >> c;
    vector<int64_t> arr(n);
    set<int64_t> s;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        s.insert(arr[i]);
    }
    arr.clear();
    for (int64_t i: s) {
        arr.push_back(i);
    }
    n = arr.size();
    vector<int64_t> pref(c + 2);
    pref[0] = 0;
    for (int i = 1; i <= c + 1; i++) {
        pref[i] = pref[i - 1] + s.count(i - 1);
    }
    if (!s.count(1)) {
        cout << "No\n";
        return;
    }
    for (int64_t i = 1; i <= c; i++) {
        if (s.count(i)) {
            continue;
        }
        for (int x = 0; x < n; x++) {
            if (arr[x] * i > c) {
                break;
            }
            if (contains(pref, arr[x] * i, min(arr[x] * i + arr[x] - 1, c))) {
                cout << "No\n";
                return;
            }
        }
    }
    cout << "Yes\n";
}
int main() {
    srand(time(nullptr));
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}
