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

using namespace std;
typedef int64_t ll;
class RMQ {
public:
    vector<vector<int>> dp;
    int query (int l, int r) {
//        cout << l << " " << r << '\n';
        int sz = log2(r - l + 1);
        int ans = min(dp[l][sz], dp[r - (1 << sz) + 1][sz]);
//        cout << l << " " << r << '\n';
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
vector<set<int>> oc;
vector<int> arr;
bool comp (pair<pair<int,int>,int> p1, pair<pair<int,int>,int> p2) {
    assert(sq != -1);
    return ((pair<int,int>){p1.first.first/sq, p1.first.second} < (pair<int,int>){p2.first.first/sq, p2.first.second});
}
int prevOc (set<int>& s, int ind) {
    assert(s.find(ind) != s.end());
    auto it = s.lower_bound(ind);
    if (it == s.begin()) return -1;
    it--;
    return *it;
}
int nxtOc (set<int>& s, int ind) {
    auto it = s.upper_bound(ind);
    if (it == s.end()) return -1;
    return *it;
}
void addRight (int ind) {
    assert(ind == r + 1);
    r++;
    if (prevOc(oc[arr[ind]], ind) < l) {
        ans++;
        return;
    }
    int i = prevOc(oc[arr[ind]], ind);
    if (rmq.query(i, ind) == arr[i]) {
        return;
    }
    ans++;
}
void removeRight (int ind) {
    assert(ind == r);
    r--;
    if (prevOc(oc[arr[ind]], ind) < l) {
        ans--;
        return;
    }
    int i = prevOc(oc[arr[ind]], ind);
    if (rmq.query(i, ind) == arr[i]) {
        return;
    }
    ans--;
}
void removeLeft (int ind) {
    assert(ind == l);
    l++;
    if (nxtOc(oc[arr[ind]], ind) > r || nxtOc(oc[arr[ind]], ind) == -1) {
        ans--;
        return;
    }
    int i = nxtOc(oc[arr[ind]], ind);
    if (rmq.query(ind, i) == arr[i]) {
        return;
    }
    ans--;
}
void addLeft (int ind) {
    assert(ind == l - 1);
    l--;
    if (nxtOc(oc[arr[ind]], ind) > r || nxtOc(oc[arr[ind]], ind) == -1) {
        ans++;
        return;
    }
    int i = nxtOc(oc[arr[ind]], ind);
    if (rmq.query(ind, i) == arr[i]) {
        return;
    }
    ans++;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N, Q;
    cin >> N >> Q;
    oc.resize(N), arr.resize(N);
    for (int i = 0; i < N; i++) {
        cin >> arr[i]; arr[i]--;
        oc[arr[i]].insert(i);
    }
    rmq.update(arr);
    sq = sqrt(N);
    vector<pair<pair<int,int>,int>> vec(Q);
    for (int i = 0; i < Q; i++) {
        cin >> vec[i].first.first >> vec[i].first.second;
        vec[i].first.first--, vec[i].first.second--;
        vec[i].second = i;
    }
    sort(vec.begin(), vec.end(), comp);
    vector<int> res;
    res.resize(Q);
    for (auto& pr: vec) {
        pair<int,int> p = pr.first;
//        cout << "PAIR " << p.first << " " << p.second << '\n';
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
        //cout << ans << '\n';
        res[pr.second] = ans;
    }
    for (int i: res) {
        cout << i << '\n';
    }
}
