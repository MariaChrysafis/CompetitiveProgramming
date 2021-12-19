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

string s;

int checker (int l, int r) {
    int t = 0;
    for (int i = l; i <= r; i++) {
        if ((i - l) % 2 == 0) {
            if (s[i] == 'b') {
                return -1;
            }
        } else {
            if (s[i] == 'a') {
                return -1;
            }
        }
        t += (s[i] == '?');
    }
    return t;
}

pair<int,int> best (pair<int,int> p1, pair<int,int> p2) {
    if (p1.first == p2.first) {
        if (p1.second < p2.second) {
            return p1;
        } else {
            return p2;
        }
    } else {
        if (p1.first < p2.first) {
            return p2;
        } else {
            return p1;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n; cin >> n;
    cin >> s;
    int x;
    cin >> x;
    vector<pair<int,int>> dp; //[maximum possible occurences, minimum number of replacements]
    dp.assign(n + 1, {0, 0});
    for (int i = 1; i <= n; i++) {
        if (i - x < 0) continue;
        dp[i] = dp[i - 1];
        int c = checker(i - x, i - 1);
        if (c != -1) {
            dp[i] = best(dp[i], {dp[i - x].first + 1, dp[i - x].second + c});
        }
        //cout << dp[i].first << " " << dp[i].second << '\n';
    }
    cout << dp[n].second;
}
