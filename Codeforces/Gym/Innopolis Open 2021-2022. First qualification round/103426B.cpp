#include <iostream>
#include <cmath>
#include <vector>
#include <set>
#include <chrono>
#include <random>
#include <queue>
#include <cassert>
#include <map>
#include <algorithm>
#define ll long long
using namespace std;
const int MOD = 1e9 + 7;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    int inp[n - 1][n];
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n; j++) {
            cin >> inp[i][j];
        }
    }
    vector<int> missing;
    missing.assign(n, 0);
    for (int i = 0; i < n; i++) {
        map<int,int> myMap;
        for (int j = 0; j < n - 1; j++) {
            myMap[inp[j][i]]++;
        }
        for (auto& p: myMap) {
            if (p.second >= 2) {
                missing[i] = -1;
            }
        }
        if (missing[i] != -1) {
            for (int j = 1; j <= n; j++) {
                if (myMap[j] == 0) {
                    missing[i] = j;
                }
            }
        }
    }
    set<int> known;
    map<int,int> myMap;
    for (int i = 0; i < missing.size(); i++) {
        //cout << missing[i] << ' ';
        if (missing[i] != -1) {
            known.insert(missing[i]);
            myMap[missing[i]]++;
        }
    }
    ll ans = 1;
    for (auto & p: myMap) {
        ans *= p.second;
        ans %= MOD;
    }
    for (int i = 1; i <= n - known.size(); i++) {
        ans *= i;
        ans %= MOD;
    }
    //ans *= (n - known.size());
    cout << known.size() << " " << ans % MOD;


}
