#include <vector>
#include <chrono>
#include <iostream>
#include <map>
#include <set>
#include <climits>
#include <cmath>
#include <cassert>
#include <iomanip>
#include <stack>
#include <queue>
#include <algorithm>
#include <string>

#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")

using namespace std;

typedef long long ll;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll n;
    cin >> n;
    vector<ll> powr = {1};
    while (powr.size() != 59) {
        powr.push_back(2 * powr.back());
    }
    set<int> s;
    int lg2 = 9;
    for (int i = 0; i < (1 << lg2); i++) {
        ll ans = 0;
        for (int j = 0; j < lg2; j++) {
            if ((1 << j) & i) {
                ans += pow(10, j);
            }
        }
        //cout << ans << '\n';
        s.insert(ans);
    }
    int cntr = 0;
    for (int i: s) {
        if (i <= n && i != 0) {
            cntr++;
        }
    }
    cntr += (n == (int)1e9);
    cout << cntr;
}
