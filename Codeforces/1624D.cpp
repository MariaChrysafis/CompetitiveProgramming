#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <set>
#include <map>
#include <cassert>
#include <ctime>
#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")

using namespace std;

void solve () {
    int N, K;
    cin >> N >> K;
    string s;
    cin >> s;
    sort(s.begin(), s.end());
    vector<bool> hasVisited;
    hasVisited.assign(s.length(), false);
    multiset<int> sizes;
    for (int i = 0; i < K; i++) {
        sizes.insert(0);
    }
    for (int i = 0; i < s.length() - 1; i++) {
        //s[i] and s[i + 1]
        if (s[i] == s[i + 1] && !hasVisited[i] && !hasVisited[i + 1]) {
            hasVisited[i] = true;
            hasVisited[i + 1] = true;
            auto it = sizes.begin();
            int x = *it;
            sizes.erase(it);
            sizes.insert(x + 2);
        }
    }
    map<int,int> oc;
    for (int j: sizes) {
        oc[j]++;
    }
    int cntr = 0;
    for (int i = 0; i < s.length(); i++) {
        if (!hasVisited[i]) {
            cntr++;
        }
    }
    if (oc[*sizes.begin()] - oc[*sizes.begin() + 2] - cntr <= 0) {
        cout << *sizes.begin() + 1 << '\n';
    } else {
        cout << *sizes.begin() << '\n';
    }
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
