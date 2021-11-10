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
#define ll int
#include <map>

using namespace std;
const int VAL = 2e5;
struct BIT {
    long long M[VAL], A[VAL];
    BIT() {
        for (int i = 0; i < VAL; i++) {
            M[i] = A[i] = 0;
        }
    }
    void update(int i, long long mul, long long add) {
        while (i < VAL) {
            M[i] += mul;
            A[i] += add;
            i |= (i + 1);
        }
    }
    void upd(int l, int r, long long x) {
        update(l, x, -x * (l - 1));
        update(r, -x, x * r);
    }
    long long query(int i) {
        long long mul = 0, add = 0;
        int st = i;
        while (i >= 0) {
            mul += M[i];
            add += A[i];
            i = (i & (i + 1)) - 1;
        }
        return (mul * st + add);
    }
    long long query(int l, int r) {
        return query(r) - query(l - 1);
    }
} t;
struct Tree{
    vector<vector<int>> adj;
    vector<int> last, first;
    vector<int> euler;
    int counter = 0;
    void pre_euler(){
        euler.resize( 2 * adj.size()), first.resize(adj.size()), last.resize(adj.size());
        dfs(0, -1, 0);
        for (int i = 0; i < adj.size(); i++) {
            euler[first[i]] = i;
            euler[last[i]] = i;
        }
    }
    void dfs(int node, int parent, int h){
        first[node] = counter++;
        for(int i: adj[node]){
            if(i != parent){
                dfs(i, node, h + 1);
            }
        }
        last[node] = counter++;
    }
};
map<int,set<pair<int,int>>> myMap; //map an integer to which integers have that thing
int main() {
    freopen("snowcow.in", "r", stdin);
    freopen("snowcow.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N, Q;
    cin >> N >> Q;
    Tree t;
    t.adj.resize(N);
    BIT st;
    for (int i = 0; i < N - 1; i++) {
        int u, v;
        cin >> u >> v;
        t.adj[--u].push_back(--v);
        t.adj[v].push_back(u);
    }
    t.pre_euler();
    while (Q--) {
        int dum;
        cin >> dum;
        if (dum == 1) {
            int x, c;
            cin >> x >> c;
            x--;
            vector<pair<int,int>> removal;
            bool fine = true;
            for (pair<int,int> p: myMap[c]) {
                if (p.first <= t.first[x] && p.second >= t.last[x]) {
                    fine = false;
                }
            }
            if (!fine) {
                continue;
            }
            for (pair<int,int> p: myMap[c]) {
                if (p.first > t.first[x] && p.second < t.last[x]) {
                    removal.push_back(p);
                }
            }
            for (auto p: removal) {
                st.upd(p.first, p.second, -1);
                myMap[c].erase(p);
            }
            st.upd(t.first[x], t.last[x], 1);
            myMap[c].insert({t.first[x], t.last[x]});
        } else {
            int x;
            cin >> x;
            x--;
            long long ans = st.query(t.first[x], t.last[x]);
            cout << ans/2 << '\n';
        }
    }
}
