//verified on https://open.kattis.com/problems/shortestpath1 
#include <iostream>
#include <cmath>
#include <vector>
#include <queue>
using namespace std;
const int INF = pow(10,9);
struct graph{
	vector<vector<pair<int,int>>> adj; //{-weight, node}
	vector<int> dijk(int src){
		vector<int> dist;
		vector<bool> mark;
		dist.resize(adj.size()), mark.resize(adj.size());
		for(int i = 0; i < adj.size(); i++){
			dist[i] = INF;
			mark[i] = false;
		}
		dist[src] = 0;
		priority_queue<pair<int,int>> pq;
		pq.push({0,src});
		while(!pq.empty()){
			int u = pq.top().second; //node
			pq.pop();
			if(mark[u]){
				continue;
			}
			mark[u] = true;
			for(auto p: adj[u]){
				int v = p.second;
				int w = p.first;
				if(dist[v] > dist[u] + w){
					dist[v] = dist[u] + w;
					pq.push({-dist[v], v});
				}
			}
		}
		return dist;
	}
};
void print(vector<int> v){
	for(int i: v){
		cout << i << " ";
	}
	cout << endl;
}
void query(int n, int m, int q, int s){
	graph g;
	g.adj.resize(n);
	while(m--){
		int u, v, w;
		cin >> u >> v >> w;
		g.adj[u].push_back({w,v});
	}
	vector<int> dist = g.dijk(s);
	//for(int i: dist) cout << i << endl;
	while(q--){
		int u;
		cin >> u;
		if(dist[u] == INF){
			cout << "Impossible" << endl;
		}else{
			cout << dist[u] << endl;
		}
	}
	cout << endl;
}
int main(){
	while(true){
		int n, m, q, s;
		cin >> n >> m >> q >> s;
		if(n == m && m == q && n == 0 && s == 0) break;
		query(n, m, q, s);
	}
}
