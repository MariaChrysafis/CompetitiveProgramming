#include <iostream>
#include <vector>
#include <chrono>
#include <cstdint>
#include <algorithm>
#include <string>
#include <set>
#include <cmath>
#include <queue>
#include <deque>
#include <cassert>
#include <fstream>
#include <map>
#include <iomanip>
#include <sstream>

using namespace std;
typedef long long ll;
vector<int> arr;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N;
    cin >> N;
    arr.resize(N);
    int K = 0;
    for (int i = 0; i < N; i++) {
        cin >> arr[i];
        arr[i]--;
        K = max(K, arr[i] + 1);
    }
    ll orig[K];
    for (int i = 0; i < K; i++) {
        orig[i] = 0;
        int cntr = 0;
        for (int j = 0; j < N; j++) {
            if (arr[j] == i) {
                orig[i] += abs(j - cntr);
                cntr++;
            }
        }
    }
    ll cost1[K][K]; //move all i to front
    for (int i = 0; i < K; i++) {
        for (int j = 0; j < K; j++) {
            cost1[i][j] = 0;
            int cntr = 0;
            for (int ind = 0; ind < N; ind++) {
                if (arr[ind] == i) {
                    cntr++;
                }
                if (arr[ind] == j) {
                    cost1[i][j] += cntr;
                }
            }
        }
    }
    ll cost[(1 << K)][K]; //change in cost of i if we move all of mask to the front
    for (int i = 0; i < (1 << K); i++) {
        for (int j = 0; j < K; j++) {
            cost[i][j] = 1e8;
        }
    }
    for (int i = 0; i < K; i++) {
        cost[0][i] = 0;
    }
    for (int mask = 1; mask < (1 << K); mask++) {
        for (int i = 0; i < K; i++) {
            for (int j = 0; j < K; j++) {
                if (((1 << j) & mask) && i != j) {
                    cost[mask][i] = cost[mask - (1 << j)][i] + cost1[j][i];
                    break;
                }
            }
        }
    }
    ll dp[(1 << K)];
    dp[0] = 0;
    for (int mask = 1; mask < (1 << K); mask++) {
        dp[mask] = 0;
        for (int i = 0; i < K; i++) {
            if (mask & (1 << i)) {
                dp[mask] = max(dp[mask - (1 << i)] + cost[mask - (1 << i)][i], dp[mask]);
            }
        }
    }
    ll cnt = 0;
    for (ll j: orig) {
        cnt += j;
    }
    cout << cnt - dp[(1 << K) - 1] << '\n';

}
