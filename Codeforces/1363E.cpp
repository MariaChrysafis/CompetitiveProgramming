#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <cmath>
#include <random>
using namespace std;
struct tree{
    long long n;
    vector<long long> a, b, c, d;
    vector<vector<long long>> adj;
    //x1 --> 1 in cur; 0 in prev
    //x2 --> 0 in cur; 1 in prev
    //cur --> current node
    //prev --> previous node
    long long ans = 0;
    void dfs(int cur, int prev){
        long long sum = abs(d[cur]);
        for(int i: adj[cur]){
            if(i == prev) continue;
            a[i] = min(a[i], a[cur]);
            dfs(i, cur);
            d[cur] += d[i];
            sum += abs(d[i]);
        }
        ans += (sum - abs(d[cur])) * a[cur];
    }
    void read(){
        cin >> n;
        a.resize(n), b.resize(n), c.resize(n), adj.resize(n);
        long long sum = 0;
        for(int i = 0; i < n; i++) cin >> a[i] >> b[i] >> c[i], d.push_back(b[i] - c[i]), sum += d.back();
        long long u, v;
        for(int i = 0; i < n - 1; i++) cin >> u >> v, u--, v--, adj[u].push_back(v), adj[v].push_back(u);
        dfs(0, -1);
        if(sum) cout << -1 << endl;
        else cout << ans << endl;
    }
};
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    tree t;
    t.read();
}
