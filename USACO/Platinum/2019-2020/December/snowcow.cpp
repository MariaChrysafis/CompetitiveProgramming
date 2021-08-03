#include <iostream>
#include <vector>
#include <set>
#include <fstream>
using namespace std;
void setIO(string s) { // the argument is the filename without the extension
    freopen((s+".in").c_str(),"r",stdin);
    freopen((s+".out").c_str(),"w",stdout);
}
void print(vector<int> v){
    for(int i: v) cout << i << ' ';
    cout << endl;
}
template<class T>
struct Seg {
    const T ID = 0;

    T comb(T a, T b) { return a + b; }

    int n;
    vector<T> seg;

    void init(int _n) {
        n = _n;
        seg.assign(2 * n, ID);
    }

    void pull(int p) { seg[p] = comb(seg[2 * p], seg[2 * p + 1]); }

    void upd(int p, T val) {
        seg[p += n] += val;
        for (p /= 2; p; p /= 2) pull(p);
    }

    T query(int l, int r) {
        T ra = ID, rb = ID;
        for (l += n, r += n + 1; l < r; l /= 2, r /= 2) {
            if (l & 1) ra = comb(ra, seg[l++]);
            if (r & 1) rb = comb(seg[--r], rb);
        }
        return comb(ra, rb);
    }
};

struct Tree{
    vector<vector<int>> adj;
    vector<int> st, en, sub;
    int counter = 0;
    int dfs1(int node, int prev){
        sub[node] = 1;
        for(int i: adj[node]){
            if(i != prev){
                sub[node] += dfs1(i, node);
            }
        }
        return sub[node];
    }
    void dfs(int node, int parent) {
        st[node] = counter, counter++;
        for (int i : adj[node]) {
            if (i != parent) {
                dfs(i, node);
            }
        }
        en[node] = counter;
        counter++;
    }
};
const int MAX = 1e5 + 1;
set<pair<int,int>> important[MAX];
Seg<int> A, B;
Tree t;
void update(int u, int x){
    A.upd(t.st[u], x);
    A.upd(t.en[u], -x);
    B.upd(t.st[u], x * t.sub[u]);
}
int main() {
    setIO("snowcow");
    int N, Q;
    cin >> N >> Q;
    t.adj.resize(N), t.st.resize(N), t.en.resize(N), t.sub.resize(N);
    for(int i = 0; i < N - 1; i++){
        int u, v;
        cin >> u >> v;
        u--, v--;
        t.adj[u].push_back(v);
        t.adj[v].push_back(u);
    }
    t.dfs(0, -1);
    t.dfs1(0, -1);
    A.init(2 * N + 1);
    B.init(2 * N + 1);
    while(Q--){
        int dum;
        cin >> dum;
        if(dum == 2){
            int u;
            cin >> u;
            u--;
            cout << t.sub[u] * A.query(0, t.st[u]) + B.query(t.st[u] + 1, t.en[u]) << '\n';
        }else{
            int u, col;
            cin >> u >> col;
            u--, col--;
            auto it = important[col].upper_bound({t.st[u], u});
            if (it != important[col].begin() && t.en[prev(it)->second] >= t.en[u]) {
                continue;
            }
            while (it != important[col].end() && t.en[it->second] <= t.en[u]) {
                update(it->second,-1);
                important[col].erase(it++);
            }
            important[col].insert({t.st[u], u});
            update(u,1);
        }
    }
}
