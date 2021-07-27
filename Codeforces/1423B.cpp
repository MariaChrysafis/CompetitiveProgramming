#include <iostream>
#include <vector>
#include <map>
#include <cassert>
#include <set>
#include <unordered_set>
#include <algorithm>
#include <random>
#include <chrono>
#include <queue>
 
#define ll long long
 
using namespace std;
struct matching {
    int n, m;
    vector<int> pa;
    vector<int> pb;
    vector<vector<int>> g;
    vector<int> q;
    vector<int> was;
    vector<int> unmatched;
    matching(int n, int m) : n(n), m(m) {
        pa.resize(n, -1);
        pb.resize(m, -1);
        g.resize(n);
        q.resize(n);
        was.resize(n);
        unmatched.resize(n);
        iota(unmatched.begin(), unmatched.end(), 0);
    }
    void add(int u, int v) {
        assert(u >= 0 && u < n && v >= 0 && v < m);
        g[u].push_back(v);
    }
    bool bfs() {
        int beg = 0, end = 0;
        for (int i = 0; i < n; i++) if (pa[i] == -1) {
                q[end++] = i;
                was[i] = 1;
            }
            else was[i] = 0;
        bool found = false;
        while (beg < end) {
            int v = q[beg++];
            for (auto& u : g[v]) {
                if (pb[u] == -1) {
                    found = true;
                    continue;
                }
                if (was[pb[u]]) continue;
                was[pb[u]] = was[v] + 1;
                q[end++] = pb[u];
            }
        }
        return found;
    }
    bool dfs(int v, int w = 1) {
        for (auto& u : g[v]) {
            if (pb[u] == -1) {
                pb[u] = v;
                pa[v] = u;
                return true;
            }
        }
        for (auto& u : g[v]) {
            if (was[pb[u]] == w + 1) {
                was[pb[u]] = 0;
                if (dfs(pb[u], w + 1)) {
                    pb[u] = v;
                    pa[v] = u;
                    return true;
                }
            }
        }
        return false;
    }
    int solve() {
        int res = 0;
        while (bfs()) {
            int add = 0;
            for (int i = 0; i < (int) unmatched.size(); i++) if (dfs(unmatched[i])) {
                    swap(unmatched[i], unmatched.back());
                    unmatched.pop_back();
                    --i;
                    ++add;
                }
            if (!add) break;
            res += add;
        }
        return res;
    }
};
vector<int> a, b, c;
int n, m;
bool isValid(int weight){
    matching bg(n, n);
    //cout << bg.solve() << endl;
    for(int i = 0; i < m; i++){
        if(c[i] < weight){
            //cout << "YES\n";
            bg.add(a[i], b[i]);
        }
    }
    //cout << v
    return (bg.solve() == n);
}
int binSearch(int l,int r){
    int m = (l + r)/2;
    if(l == r) return l;
    if(isValid(m)){
        return binSearch(l, m);
    }else{
        return binSearch(m + 1, r);
    }
}
int main(){
    cin >> n >> m;
    a.resize(m), b.resize(m), c.resize(m);
    for(int i = 0; i < m; i++){
        cin >> a[i] >> b[i] >> c[i];
        a[i]--, b[i]--;
    }
    const int MAX = 1e9;
    int ans = binSearch(0, MAX);
    if(ans == MAX) cout << -1;
    else cout << ans - 1 << endl;
}
