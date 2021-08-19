#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include <set>
#include <map>
 
#define ll long long
using namespace std;
void print(vector<int> v){
    for(int i: v) cout << i << " ";
    cout << endl;
}
struct LazyST {
    vector<pair<ll,ll>> tree;
    vector<pair<ll,ll>> lazy;
    int N;
    pair<ll,ll> NONE;
 
    LazyST(int n) {
        N = n;
        NONE = {-1LL, -1LL};
        tree.assign(4 * N + 1, {0LL, -1LL});
        lazy.assign(4 * N + 1, {0LL, -1LL});
    }
 
    void update(int L, int R, pair<ll,ll> val) {
        update(0, 0, N - 1, L, R, val);
    }
 
    void update(int n, int L, int R, int uL, int uR, pair<ll,ll> val) {
        push(n, L, R);
        if (uL <= L && R <= uR) {
            lazy[n] = max(lazy[n], val);
            push(n, L, R);
            return;
        } else if (L > uR || R < uL || L == R) {
            return;
        }
        update(2 * n + 1, L, (L + R) / 2, uL, uR, val);
        update(2 * n + 2, (L + R) / 2 + 1, R, uL, uR, val);
        tree[n] = merge(tree[2 * n + 1], tree[2 * n + 2]);
    }
 
    pair<ll,ll> query(int L, int R) {
        return query(0, 0, N - 1, L, R);
    }
 
    pair<ll,ll> query(int n, int L, int R, int Lq, int Rq) {
        push(n, L, R);
        if (Lq <= L && R <= Rq) {
            return tree[n];
        } else if (R < Lq || Rq < L) {
            return NONE;
        } else {
            return merge(query(2 * n + 1, L, (L + R) / 2, Lq, Rq), query(2 * n + 2, (L + R) / 2 + 1, R, Lq, Rq));
        }
    }
 
    void push(int n, int L, int R) {
        tree[n] = max(lazy[n], tree[n]);
 
        if (L < R) {
            lazy[2 * n + 1] = max(lazy[2 * n + 1], lazy[n]);
            lazy[2 * n + 2] = max(lazy[2 * n + 2], lazy[n]);
        }
        lazy[n] = {0LL, -1LL};
    }
 
    pair<ll,ll> merge(pair<ll,ll> a, pair<ll,ll> b) {
        return max(a, b); //max,NONE=NEG INF
    }
};
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, int>>> intervals(n);
    set<int> spec;
    map<int, int> myMap;
    for (int i = 0; i < m; i++) {
        int j, l, r;
        cin >> j >> l >> r;
        j--;
        intervals[j].push_back({l, r});
        spec.insert(l), spec.insert(r);
    }
    int myCntr = 0;
    for (auto it = spec.begin(); it != spec.end(); it++) {
        myMap[*it] = myCntr;
        myCntr++;
    }
    int myMax = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < intervals[i].size(); j++) {
            intervals[i][j].first = myMap[intervals[i][j].first];
            intervals[i][j].second = myMap[intervals[i][j].second];
            myMax = max(myMax, max(intervals[i][j].first, intervals[i][j].second));
        }
    }
    LazyST st(myMax + 1);
    st.update(0, myMax, {0, -1LL});
    vector<int> dp(n);
    vector<int> par(n);
    for(int i = 0; i < n; i++) par[i] = -1, dp[i] = 0;
    for(int i = 0; i < n; i++){
        dp[i] = 1;
        for(pair<int,int> p: intervals[i]){
            pair<ll,ll> pr = st.query(p.first, p.second);
            if(pr.first + 1 > dp[i]){
                dp[i] = pr.first + 1;
                par[i] = pr.second;
            }
        }
        for(pair<int,int> p: intervals[i]){
            st.update(p.first, p.second, {dp[i],i});
        }
    }
    int ind = 0;
    for(int i = 0; i < n; i++){
        if(dp[i] > dp[ind]) {
            ind = i;
        }
    }
    cout << n - dp[ind] << endl;
    if(n == dp[ind]){
        return 0;
    }
    map<int,bool> mm;
    while(ind >= 0){
        mm[ind] = true;
        ind = par[ind];
    }
    for(int i = 0; i < n; i++){
        if(!mm[i]){
            cout << i + 1 << " ";
        }
    }
 
 
}
