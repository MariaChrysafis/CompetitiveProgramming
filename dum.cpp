#include <cmath>
#include <cassert>
#include <iostream>
#include <set>
#include <climits>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <bitset>
#include <type_traits>
#include <string>
#include <queue>
#include <map>
#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")

using namespace std;
class RMQ {
public:
    vector<vector<int>> dp;
    int query (int l, int r) {
        int sz = log2(r - l + 1);
        int ans = min(dp[l][sz], dp[r - (1 << sz) + 1][sz]);
        return ans;
    }
    void update (vector<int> arr) {
        dp.resize(arr.size());
        for (int i = 0; i < arr.size(); i++) {
            dp[i].resize(32);
        }
        for (int j = 0; j <= 31; j++) {
            for (int i = 0; i < arr.size(); i++) {
                if (j == 0) {
                    dp[i][j] = arr[i];
                    continue;
                }
                dp[i][j] = min(dp[min(i + (1 << (j - 1)), (int)arr.size() - 1)][j - 1], dp[i][j - 1]);
            }
        }
    }
};
RMQ rmq;
int l = 0;
int r = -1;
int sq = -1;
int ans = 0;
vector<vector<int>> oc;
vector<int> arr;
vector<int> indices;
vector<int> bef;
vector<int> nxt;
vector<int> bef_val, nxt_val;
bool comp (pair<pair<int,int>,int> p1, pair<pair<int,int>,int> p2) {
    return ((pair<int,int>){p1.first.first/sq, p1.first.second} < (pair<int,int>){p2.first.first/sq, p2.first.second});
}
int prevOc (int ind) {
    if (indices[ind] == 0) return -1;
    return oc[arr[ind]][indices[ind] - 1];
}
int nxtOc (int ind) {
    if (indices[ind] + 1 == oc[arr[ind]].size()) return -1;
    return oc[arr[ind]][indices[ind] + 1];
}
void addRight (int ind) {
    r++;
    if (bef[ind] < l || bef_val[ind] != arr[ind]) {
        ans++;
        return;
    }
}
void removeRight (int ind) {
    r--;
    if (bef[ind] < l || bef_val[ind] != arr[ind]) {
        ans--;
        return;
    }
}
void removeLeft (int ind) {
    l++;
    if (nxt[ind] > r || nxt[ind] == -1 || nxt_val[ind] != arr[ind]) {
        ans--;
    }
}
void addLeft (int ind) {
    l--;
    if (nxt[ind] > r || nxt[ind] == -1 || nxt_val[ind] != arr[ind]) {
        ans++;
        return;
    }
}
int main() {
    //freopen("output.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N, Q;
    cin >> N >> Q;
    oc.resize(N), arr.resize(N), indices.resize(N);
    for (int i = 0; i < N; i++) {
        cin >> arr[i]; arr[i]--;
        indices[i] = oc[arr[i]].size();
        oc[arr[i]].push_back(i);
    }
    rmq.update(arr);
    sq = 550;
    vector<pair<pair<int,int>,int>> vec(Q);
    for (int i = 0; i < Q; i++) {
        cin >> vec[i].first.first >> vec[i].first.second;
        vec[i].first.first--, vec[i].first.second--;
        vec[i].second = i;
    }
    sort(vec.begin(), vec.end(), comp);
    bef.resize(N), bef_val.resize(N);
    nxt.resize(N), nxt_val.resize(N);
    for (int i = 0; i < N; i++) {
        bef[i] = prevOc(i);
        nxt[i] = nxtOc(i);
    }
    for (int i = 0; i < N; i++) {
        if (bef[i] < i && bef[i] != -1) {
            bef_val[i] = rmq.query(bef[i], i);
        }
        if (nxt[i] > i && nxt[i] != -1) {
            nxt_val[i] = rmq.query(i, nxt[i]);
        }
    }
    vector<int> res;
    res.resize(Q);
    for (auto& pr: vec) {
        pair<int,int> p = pr.first;
        while (r < p.second) {
            addRight(r + 1);
        }
        while (r > p.second) {
            removeRight(r);
        }
        while (l < p.first) {
            removeLeft(l);
        }
        while (l > p.first) {
            addLeft(l - 1);
        }
        res[pr.second] = ans;
    }
    for (int i: res) {
        cout << i << '\n';
    }
}
