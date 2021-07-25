#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <unordered_set>
#include <algorithm>
#include <random>
#include <chrono>
#include <queue>
#define ll int64_t
using namespace std;
struct triple{
    int64_t curContrib;
    int64_t willContrib;
    int64_t weight;
    int u, v;
};
struct customCompare{
    bool operator()(const triple& lhs, const triple& rhs){
        return (lhs.curContrib - lhs.willContrib < rhs.curContrib - rhs.willContrib);
    }
};
void print(priority_queue<triple, vector<triple>, customCompare> pq){
    while(!pq.empty()){
        cout << pq.top().curContrib - pq.top().willContrib << endl;
        pq.pop();
    }
    cout << endl;
}
struct tree{
    uint64_t n, S;
    vector<vector<pair<int64_t,int64_t>>> adj;
    vector<int64_t> sub;
    int64_t ans = 0;
    int64_t dfs(int cur, int prev){
        if(adj[cur].size() == 1 && cur != 0){
            sub[cur] = 1;
            return 1;
        }
        //how many leaves are in its subtree
        int cntr = 0;
        for(pair<int,int> p: adj[cur]){
            if(p.first != prev){
                cntr += dfs(p.first, cur);
            }
        }
        sub[cur] = cntr;
        return cntr;
    }
    void read(){
        cin >> n >> S;
        adj.resize(n), sub.resize(n);
        for(int i = 0; i < n - 1; i++){
            int64_t u, v, w;
            cin >> u >> v >> w;
            u--, v--;
            while(w > S){
                ans++;
                w = w/2;
            }
            adj[u].push_back({v,w}), adj[v].push_back({u,w});
        }
        dfs(0, -1);
        priority_queue<triple, vector<triple>, customCompare> pq;
        uint64_t sum = 0;
        for(int i = 0; i < n; i++){
            for(pair<int64_t,int64_t> p: adj[i]){
                if(p.first > i) continue;
                triple t;
                t.u = i, t.v = p.first, t.curContrib = p.second * min(sub[i], sub[p.first]);
                t.willContrib = p.second/2 * min(sub[i], sub[p.first]);
                t.weight = p.second;
                sum += t.curContrib;
                //cout << t.u << " " << t.v << " " << t.curContrib << endl;
                pq.push(t);
            }
        }
        //cout << sum << endl;
        while(sum > S){
            triple cur = pq.top();
            pq.pop();
            triple next;
            next.weight = cur.weight/2;
            next.u = cur.u, next.v = cur.v, next.curContrib = cur.willContrib;
            next.willContrib = next.weight/2 * min(sub[next.v], sub[next.u]);
            sum -= (cur.curContrib - cur.willContrib);
            pq.push(next);
            ans++;
        }
        //cout << ans << endl;
        //print(pq);
    }
};
 
void solve() {
    tree t;
    t.read();
    cout << t.ans << endl;
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while(t--) {
        solve();
    }
}
