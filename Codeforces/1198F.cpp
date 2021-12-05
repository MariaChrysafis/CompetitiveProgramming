#include <iostream>
#include <cmath>
#include <vector>
#include <set>
#include <chrono>
#include <random>
#include <queue>
#include <cstdint>
#include <cassert>
#include <bit>
#include <bitset>
#include <map>
#include <list>
#include <stack>
#include <algorithm>

#pragma GCC optimize("O1")
#pragma GCC optimize("O2")
#pragma GCC optimize("O3")
#define ll long long
using namespace std;
int gcd (int x, int y) {
    if (min(x, y) == 0) return max(x, y);
    return gcd(max(x, y) % min(x, y), min(x, y));
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    vector<pair<int,int>> arr(n);
    map<int,int> index;
    for (int i = 0; i < n; i++) {
        cin >> arr[i].first; arr[i].second = i;
    }
    int x = 3e6/n;
    while(x--) {
        random_shuffle (arr.begin(), arr.end() );
        int l = 0; int r = 0;
        int ans[n];
        for (int i = 0; i < n; i++) {
            if (gcd(l, arr[i].first) != l) {
                l = gcd(l, arr[i].first);
                ans[arr[i].second] = 2;
            } else {
                r = gcd(r, arr[i].first);
                ans[arr[i].second] = 1;
            }
        }
        if (r == 1 && l == 1) {
            cout << "YES\n";
            for (int i = 0; i < n; i++) {
                cout << ans[i] << ' ';
            }
            cout << '\n';
            return 0;
        }
    }
    cout << "NO\n";
}
