#include <vector>
#include <algorithm>
#include <iostream>
#include <set>
#include <cmath>
#include <map>
#include <random>
#include <cassert>
#include <ctime>
#include <bitset>
#include <stack>
#include <cstdlib>
#include <queue>
#include <stdint.h>
#include <cstdio>
#include <limits.h>
 
using namespace std;
 
class SparseTable {
    vector<int64_t> pref;
    vector<int64_t> arr;
public:
    int64_t query (int l, int r) {
        return pref[r + 1] - pref[l];
    }
    SparseTable (vector<int64_t> arr) {
        this->arr = arr;
        pref = {0};
        for (int i = 1; i <= arr.size(); i++) {
            pref.push_back(pref.back() + arr[i - 1]);
        }
    }
};
 
vector<int64_t> powr = {1};
 
bool submask (int64_t mask, int64_t cur) {
    return ((cur | mask) == mask);
}
 
bool press (SparseTable& st, int A, int B, int N, int64_t mask) {
    int dp[N];
    for (int i = 0; i < N; i++) {
        //dp[i] = false;
        dp[i] = 1e8;
    }
    for (int i = 0; i < N; i++) {
        if (submask(mask, st.query(0, i))) {
            dp[i] = 1;
        }
    }
    for (int i = 0; i < N; i++) {
        for (int prev = 0; prev < i; prev++) {
            if (submask(mask, st.query(prev + 1, i))) {
                dp[i] = min(dp[i], dp[prev] + 1);
            }
        }
    }
    return (dp[N - 1] <= B);
}
 
bool process (SparseTable& st, int A, int B, int N, int64_t mask) {
    if (A == 1) return press(st, A, B, N, mask);
    bitset<2000> dp[N + 1];
    bitset<2000> segments[N];
    for (int i = 0; i < N; i++) {
        for (int j = i; j >= 1; j--) {
            if (st.query(j, i) > mask) {
                break;
            }
            if (submask(mask, st.query(j, i))) {
                segments[i].set(j - 1);
            }
        }
    }
    for (int i = 0; i < N; i++) {
        if (submask(mask, st.query(0, i))) {
            dp[1].set(i);
        }
    }
    for (int i = 0; i < N; i++) {
        for (int j = 2; j <= N; j++) {
            if ((dp[j - 1] & segments[i]).any()) {
                dp[j].set(i);
            }
        }
    }
    for (int j = A; j <= B; j++) {
        if (dp[j][N - 1]) {
            return true;
        }
    }
    return false;
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N, A, B;
    cin >> N >> A >> B;
    vector<int64_t> arr(N);
    for (int i = 0; i < N; i++) {
        cin >> arr[i];
    }
    SparseTable st(arr);
    while (powr.size() != 60) {
        powr.push_back(powr.back() * 2);
    }
    const int MX = 58;
    int64_t cur = powr[MX + 1] - 1;
    for (int j = MX; j >= 0; j--) {
        if (process(st, A, B, N, cur - powr[j])) {
            cur -= powr[j];
        }
    }
    cout << cur;
}
