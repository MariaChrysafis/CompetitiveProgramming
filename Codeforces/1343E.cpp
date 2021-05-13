#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
//#include <priority_queue>
const long long INF = 1e18;
using namespace std;
struct graph{
	vector<vector<pair<long long,long long>>> adj; //{-weight, node}
	vector<long long> dijk(long long src){
		vector<long long> dist;
		vector<bool> mark;
		dist.resize(adj.size()), mark.resize(adj.size());
		for(int i = 0; i < adj.size(); i++){
			dist[i] = INF;
			mark[i] = false;
		}
		dist[src] = 0;
		priority_queue<pair<long long,long long>> pq;
		pq.push({0,src});
		while(!pq.empty()){
			int u = pq.top().second; //node
			pq.pop();
			if(mark[u]){
				continue;
			}
			mark[u] = true;
			for(auto p: adj[u]){
				long long v = p.second;
				long long w = p.first;
				if(dist[v] > dist[u] + w){
					dist[v] = dist[u] + w;
					pq.push({-dist[v], v});
				}
			}
		}
		return dist;
	}
};
void print(vector<vector<pair<int,int>>> v){
    for(int i = 0; i < v.size(); i++){
        for(int j = 0; j < v[i].size(); j++){
            //cout << v[i][j].first ;
        }
    }
}
void solve(){
    int n, m, a, b, c;
    cin >> n >> m >> a >> b >> c;
    a--, b--, c--;
    vector<long long> v(m);
    for(int i = 0; i < m; i++){
        cin >> v[i];
    }
    sort(v.begin(), v.end());
    graph g;
    g.adj.resize(n);
    for(int i = 0; i < m; i++){
        long long u, v;
        cin >> u >> v;
        u--, v--;
        g.adj[u].push_back({1,v});
        g.adj[v].push_back({1,u});
    }
    //return;
    vector<long long> va = g.dijk(a);
    vector<long long> vb = g.dijk(b);
    vector<long long> vc = g.dijk(c);
    vector<long long> pref;
    pref.push_back(0);
    for(int i = 0; i < m; i++){
        pref.push_back(pref.back() + v[i]);
    }
    long long myMin = INF;
    for(int i = 0; i < n; i++){
        if(va[i] + vb[i] + vc[i] > m) continue;
        else myMin = min(myMin, pref[vb[i]] + pref[va[i] + vb[i] + vc[i]]);
    }
    cout << myMin << endl;
}
int main(){
    int t;
    cin >> t;
    while(t--){
        solve();
    }
}
