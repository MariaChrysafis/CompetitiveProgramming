#include <cmath>
#include <iostream>
#include <set>
#include <climits>
#include <cstdio>
#include <algorithm>
#include <cassert>
#include <string>
#include <vector>
#include <iomanip>
#include <unordered_map>
#include <type_traits>
#include <string>
#include <queue>
#include <map>


using namespace std;

vector<vector<int>> adj;
vector<int> color;
vector<int> sub;
vector<vector<pair<int,int>>> queries;
set<int> oc1[(int)1e5];
int oc2[(int)1e5];
int res[(int)1e5];
struct BIT{
    vector<long long> bit; //1-indexed
    long long pref(long long ind){
        long long ans = 0;
        ind++;
        while(ind > 0){
            //cout << ind << " ";
            ans += bit[ind];
            ind -= (ind & (-ind));
        }
        return ans;
    }
    long long sum(long long l, long long r){
        if(l == 0){
            return pref(r);
        }
        return pref(r) - pref(l - 1);
    }
    void update(long long ind, long long val){
        ind++;
        while(ind < bit.size()){
            bit[ind] += val;
            ind += ind & (-ind);
        }
    }
    void construct(int n){
        bit.resize(n + 1);
        for(int i = 0; i <= n; i++){
            bit[i] = 0;
        }
    }
};
BIT st;
int comp (int a, int b) {
    return (sub[a] > sub[b]);
}
void dfs_sub (int curNode, int prevNode) {
    sub[curNode] = 1;
    int p = -1;
    for (int i = 0; i < adj[curNode].size(); i++) {
        if (adj[curNode][i] != prevNode) {
            dfs_sub(adj[curNode][i], curNode);
            sub[curNode] += sub[adj[curNode][i]];
        } else {
            p = i;
        }
    }
    if (p != -1) {
        swap(adj[curNode].back(), adj[curNode][p]);
        adj[curNode].pop_back();
    }
    sort(adj[curNode].begin(), adj[curNode].end(), comp);
    reverse(adj[curNode].begin(), adj[curNode].end());
}
void Erase (int curNode, bool b) {
    st.update(oc2[color[curNode]], -1);
    oc1[oc2[color[curNode]]].erase(color[curNode]);
    oc2[color[curNode]]--;
    oc1[oc2[color[curNode]]].insert(color[curNode]);
    st.update(oc2[color[curNode]], 1);
    if (b) {
        for (int i: adj[curNode]) {
            Erase(i, b);
        }
    }
}
void Insert (int curNode, bool b) {
    st.update(oc2[color[curNode]], -1);
    oc1[oc2[color[curNode]]].erase(color[curNode]);
    oc2[color[curNode]]++;
    oc1[oc2[color[curNode]]].insert(color[curNode]);
    st.update(oc2[color[curNode]], 1);
    if (b) {
        for (int i: adj[curNode]) {
            Insert(i, b);
        }
    }
}
void dfs (int curNode, int prevNode) {
    for (int i: adj[curNode]) {
        dfs (i, curNode);
        if (i != adj[curNode].back()) {
            Erase(i, true);
        }
    }
    for (int i: adj[curNode]) {
        if (i != adj[curNode].back()) {
            Insert(i, true);
        }
    }
    Insert(curNode, false);
    for (auto [k, q]: queries[curNode]) {
        int ans = st.sum(k, (int)1e5);
        res[q] = ans;
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N, Q;
    cin >> N >> Q;
    adj.resize(N);
    color.resize(N);
    queries.resize(N);
    sub.resize(N);
    st.construct((int)1e5 + 1);
    for (int i = 0; i < N; i++) {
        cin >> color[i]; color[i]--;
        oc1[0].insert(color[i]);
    }
    for (int i = 0; i < N - 1; i++) {
        int u, v; cin >> u >> v; u--, v--;
        adj[u].push_back(v), adj[v].push_back(u);
    }
    for (int q = 0; q < Q; q++) {
        int v, k;
        cin >> v >> k;
        v--;
        queries[v].push_back({k, q});
    }
    dfs_sub(0, 0);
    dfs (0, 0);
    for (int i = 0; i < Q; i++) {
        cout << res[i] << '\n';
    }


}
