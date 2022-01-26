#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <map>
#include <algorithm>
#include <climits>
#include <cstring>
#include <set>
#include <queue>
#include <stack>
#include <list>
#include <cstring>
#include <random>
#include <array>
#include <chrono>

using namespace std;

typedef int64_t ll;

vector<vector<int>> vec;
const int MOD = 1e9 + 7;
ll mult (ll x, ll y) {
    return (x * y) % MOD;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll N, M;
    cin >> N >> M;
    ll cur = 2 * M;
    ll val = 2 * M - 1;
    ll powr = 1;
    N--;
    while (N--) {
        cur = mult(cur, val);
        cur += (powr = mult(powr, M));
        cur %= MOD;
    }
    cout << cur;
}
