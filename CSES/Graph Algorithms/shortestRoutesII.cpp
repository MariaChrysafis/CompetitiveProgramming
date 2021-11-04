#include <iostream>
#include <vector>
#define ll long long
using namespace std;
const ll INF = 100000000000000;
struct Graph{
	vector<vector<ll>> adj;
	void floyd(){
		for(int k = 0; k < adj.size(); k++){
			for(int i = 0; i < adj.size(); i++){
				for(int j = 0; j < adj.size(); j++){
					adj[i][j] = min(adj[i][k] + adj[j][k], adj[i][j]);
				}
			}
		}
	}
};
int main(){
	Graph g;
	ll n, m, q;
	cin >> n >> m >> q;
	g.adj.resize(n);
	for(int i = 0; i < n; i++){
		g.adj[i].resize(n);
		for(int j = 0; j < g.adj[i].size(); j++){
			g.adj[i][j] = INF;
		}
		g.adj[i][i] = 0;
	}
	for(int i = 0; i < m; i++){
		ll u, v, w;
		cin >> u >> v >> w;
		u--, v--;
		g.adj[u][v] = min(g.adj[u][v],w);
		g.adj[v][u] = min(g.adj[u][v], w);
	}
	g.floyd();
	while(q--){
		ll u, v;
		cin >> u >> v;
		u--, v--;
		if(g.adj[u][v] == INF){
			cout << - 1 << endl;
		}else{
			cout << g.adj[u][v] << endl;
		}
	}
}
