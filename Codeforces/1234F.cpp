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

#define ll long long
using namespace std;
const int MAX = 20;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string s;
    cin >> s;
    bool pos[(1 << MAX)];
    for (int i = 0; i < (1 << MAX); i++) {
        pos[i] = false;
    }
    int myMax = 0;
    for (int i = 0; i < s.length(); i++)  {
        int mask = 0;
        for (int j = i; j < s.length(); j++) {
            if (mask & (1 << (s[j] - 'a'))) {
                break;
            }
            mask ^= (1 << (s[j] - 'a'));
            pos[mask] = true;
            myMax = max(myMax, __builtin_popcount(mask));
        }
    }
    vector<int> dp;
    dp.assign((1 << MAX), 0);
    for (int i = 0; i < (1 << MAX); i++) {
        if (pos[i]) {
            dp[i] = max(dp[i], __builtin_popcount(i));
        }
        for (int j = 0; j < MAX; j++) {
            if (!(i & (1 << j))) {
                dp[i ^ (1 << j)] = max(dp[i ^ (1 << j)], dp[i]);
            }
        }
    }
    for (int i = 0; i < (1 << MAX); i++) {
        myMax = max(myMax, dp[(1 << MAX) - 1 - i] + dp[i]);
    }
    cout << myMax;
}
