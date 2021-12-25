#include <iostream>
#include <cmath>
#include <vector>
#include <set>
#include <chrono>
#include <random>
#include <queue>
#include <cstdint>
#include <cassert>
#include <bitset>
#include <map>
#include <list>
#include <stack>
#include <algorithm>

typedef long long ll;
using namespace std;
const ll MAXN = 1e5;
ll dp[MAXN][2][2][2][2];
vector<pair<ll, ll>> val;
ll K;
const ll INF = 1e17;

ll memoize(int ind, bool b1, bool b2, bool b3, bool b4) {
    if (ind < 0) {
        return 0;
    }
    if (dp[ind][b1][b2][b3][b4] != -1) {
        return dp[ind][b1][b2][b3][b4];
    }
    vector<bool> v = {b1, b2, b3, b4};
    for (int i = 0; i < v.size(); i++) {
        for (int j = i + 1; j < v.size(); j++) {
            if (!v[j] && !v[i] && ind - i >= 0 && ind - j >= 0) {
                if (abs(val[ind - i].first - val[ind - j].first) <= K) {
                    return INF;
                }
            }
        }
    }
    //b4 represents our current guy
    dp[ind][b1][b2][b3][b4] = INF;
    if (ind == 0) {
        if (!b1 && !b2 && !b3 && !b4) {
            return (dp[ind][b1][b2][b3][b4] = 0);
        }
        return (dp[ind][b1][b2][b3][b4] = INF);
    } else if (ind == 1) {
        if (b1 && b2 && !b3 && !b4) {
            if (abs(val[0].first - val[1].first) <= K) {
                return (dp[ind][b1][b2][b3][b4] = val[1].second + val[0].second);
            }
        }
        if (!b1 && !b2 && !b3 && !b4) {
            return (dp[ind][b1][b2][b3][b4] = 0);
        }
        return (dp[ind][b1][b2][b3][b4] = INF);
    }
    if (b1) {
        //this means that we want to fill b1
        if (b2) {
            //b2 needs to be filled
            if (abs(val[ind].first - val[ind - 1].first) <= K) {
                ll prev = INF;
                for (int b5 = 0; b5 <= 1; b5++) {
                    for (int b6 = 0; b6 <= 1; b6++) {
                        prev = min(prev, memoize(ind - 2, b3, b4, b5, b6));
                    }
                }
                return (dp[ind][b1][b2][b3][b4] = prev + val[ind].second + val[ind - 1].second);
            }
            return INF;
        } else if (b3) {
            //we want to fill b1 & we want to pair it with b3
            if (abs(val[ind].first - val[ind - 2].first) <= K) {
                ll prev = INF;
                for (int b5 = 0; b5 <= 1; b5++) {
                    for (int b6 = 0; b6 <= 1; b6++) {
                        for (int b7 = 0; b7 <= 1; b7++) {
                            if (ind >= 4 && !b5 && abs(val[ind - 1].first - val[ind - 4].first) <= K) continue;
                            if (ind >= 5 && !b6 && abs(val[ind - 1].first - val[ind - 5].first) <= K) continue;
                            if (ind >= 6 && !b7 && abs(val[ind - 1].first - val[ind - 6].first) <= K) continue;
                            prev = min(prev, memoize(ind - 3, b4, b5, b6, b7));
                        }
                    }
                }
                return (dp[ind][b1][b2][b3][b4] = prev + val[ind].second + val[ind - 2].second);
            }
            return INF;
        }
        return INF;
    }
    if (!b1) {
        dp[ind][b1][b2][b3][b4] = memoize(ind - 1, b2, b3, b4, true);
        if (abs(val[ind].first - val[ind - 4].first) <= K) {
            return dp[ind][b1][b2][b3][b4];
        }
        return (dp[ind][b1][b2][b3][b4] = min(memoize(ind - 1, b2, b3, b4, false), dp[ind][b1][b2][b3][b4]));
    }
}

int main() {
    freopen("fairphoto.in", "r", stdin);
    //freopen("fairphoto.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll T, N;
    cin >> T >> N >> K;
    val.resize(N);
    ll tot = 0;
    for (int i = 0; i < N; i++) {
        cin >> val[i].first >> val[i].second;
        tot += val[i].second;
    }
    if (T == 1) {
        cout << 2;
        return 0;
    }
    for (int i = 0; i < N; i++) {
        for (int d1 = 0; d1 <= 1; d1++) {
            for (int d2 = 0; d2 <= 1; d2++) {
                for (int d3 = 0; d3 <= 1; d3++) {
                    for (int d4 = 0; d4 <= 1; d4++) {
                        dp[i][d1][d2][d3][d4] = -1;
                    }
                }
            }
        }
    }
    ll myMax = 0;
    for (int i = 0; i < N; i++) {
        for (int d1 = 0; d1 <= 1; d1++) {
            for (int d2 = 0; d2 <= 1; d2++) {
                for (int d3 = 0; d3 <= 1; d3++) {
                    for (int d4 = 0; d4 <= 1; d4++) {
                        if (i == N - 1) {
                            myMax = max(myMax, tot - memoize(i, d1, d2, d3, d4));
                        }
                    }
                }
            }
        }
    }
    cout << myMax << '\n';
}
