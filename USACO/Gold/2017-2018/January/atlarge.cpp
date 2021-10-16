#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <cmath>
#include <queue>
#include <map>
#include <iomanip>
using namespace std;
vector<vector<int>> adj;
vector<int> parent;
void dfs (int curNode, int prevNode) {
	parent[curNode] = prevNode;
	for (int i: adj[curNode]) {
		if (i != prevNode) {
			dfs(i, curNode);
		}
	}
}
int main() {
	freopen("atlarge.in", "r", stdin);
	freopen("atlarge.out", "w", stdout);
	int n;
	int root;
	cin >> n >> root;
	root--;
	adj.resize(n);
	for (int i = 0; i < n - 1; i++) {
		int u, v;
		cin >> u >> v;
		u--, v--;
		adj[u].push_back(v), adj[v].push_back(u);
	}
	int dist[n];
	int leaf_dist[n];
	parent.resize(n);
	for (int i = 0; i < n; i++) {
		dist[i] = -1;
		leaf_dist[i] = -1;
		parent[i] = -1;
	}
	//distance from each node to the root
	queue<pair<int,int>> q;
	q.push(make_pair(root, 0));
	while (!q.empty()) {
		pair<int,int> cur = q.front();
		q.pop();
		if (dist[cur.first] != -1) {
			continue;
		}
		dist[cur.first] = cur.second;
		for (int i: adj[cur.first]) {
			q.push(make_pair(i, cur.second + 1));
		}
	}
	for (int i = 0; i < n; i++) {
		if (i != root && adj[i].size() == 1) {
			q.push({i, 0});
		}
	}
	dfs (0, -1);
	while (!q.empty()) {
		pair<int,int> cur = q.front();
		q.pop();
		if (leaf_dist[cur.first] != -1) {
			continue;
		}
		leaf_dist[cur.first] = cur.second;
		for (int i: adj[cur.first]) {
			q.push(make_pair(i, cur.second + 1));
		}
	}
	int cntr = 0;
	for (int i = 0; i < n; i++) {
		if (i == root) {
			continue;
		}
		if (leaf_dist[i] <= dist[i] && leaf_dist[parent[i]] > dist[parent[i]]) {
			cntr++;
		}
	}
	cout << cntr << endl;
}

