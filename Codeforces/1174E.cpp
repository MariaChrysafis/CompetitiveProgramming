#include <iostream>
#include <vector>
#include <chrono>
#include <cstdint>
#include <algorithm>
#include <set>
#include <cmath>
#include <queue>
#include <deque>
#include <cassert>
#include <map>

using namespace std;

typedef int64_t ll;
const int MOD = 1e9 + 7;

ll mult (ll x, ll y) {
    return (x * y) % MOD;
}

ll eval2 (int p) {
    int lg2 = log2(p);
    ll cur[lg2 + 1];
    ll prev[lg2 + 1];
    for (int i = lg2; i >= 0; i--) {
        prev[i] = cur[i] = 0;
    }
    prev[lg2] = 1;
    for (int j = 2; j <= p; j++) {
        for (int i = lg2 - 1; i >= 0; i--) {
            int available = p/(1 << i) - (j - 1);
            if (available >= 0) {
                cur[i] += mult(prev[i], available);
                int bad = p/(1 << i) - p/(1 << (i + 1));
                cur[i] += mult(prev[i + 1], bad);
                cur[i] %= MOD;
            }
        }
        for (int i = lg2; i >= 0; i--) {
            prev[i] = cur[i];
            cur[i] = 0;
        }
    }
    return prev[0];
}

vector<ll> pow3;
vector<ll> pow2;

int cnt (int p, int i, int j) {
    return p/(pow2[i] * pow3[j]);
}

ll eval3 (int p) {
    int lg2 = log2(p/3);
    int lg3 = 1;
    ll cur[lg2 + 1][lg3 + 1];
    ll prev[lg2 + 1][lg3 + 1];
    for (int i = 0; i <= lg2; i++) {
        for (int j = 0; j <= lg3; j++) {
            cur[i][j] = prev[i][j] = 0;
        }
    }
    prev[lg2][1] = 1;
    for (int k = 2; k <= p; k++) {
        for (int i = lg2; i >= 0; i--) {
            for (int j = lg3; j >= 0; j--) {
                //dp[i][j][k] has gcd 2^i * 3^j and length k
                if (i + 1 <= lg2) {
                    int available = cnt(p, i, j) - cnt(p, i + 1, j);
                    if (available >= 0) {
                        cur[i][j] += mult(prev[i + 1][j], available);
                    }
                }
                if (j + 1 <= lg3) {
                    int available = cnt(p, i, j) - cnt(p, i, j + 1);
                    if (available >= 0) {
                        cur[i][j] += mult(prev[i][j + 1], available);
                    }
                }
                int available = cnt(p, i, j) - (k - 1);
                if (available >= 0) {
                    cur[i][j] += mult(prev[i][j], available);
                }
                if (cur[i][j] >= MOD) {
                    cur[i][j] %= MOD;
                }
            }
        }
        for (int i = lg2; i >= 0; i--) {
            for (int j = lg3; j >= 0; j--) {
                prev[i][j] = cur[i][j];
                cur[i][j] = 0;
            }
        }
    }
    return prev[0][0];

}

int nearestPower (int n) {
    int lg2 = log2(n);
    return (1 << lg2);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N;
    cin >> N;
    pow3.push_back(1), pow2.push_back(1);
    while (pow3.size() != 14) {
        pow3.push_back(pow3.back() * 3);
    }
    while (pow2.size() != 21) {
        pow2.push_back(pow2.back() * 2);
    }
    if (N >= 3 && nearestPower(N/3) * 2 == nearestPower(N)) {
        cout << (eval3(N) + eval2(N)) % MOD << '\n';
    } else {
        cout << eval2(N);
    }
}
