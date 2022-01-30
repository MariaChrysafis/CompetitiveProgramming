#include <cmath>
#include <cassert>
#include <iostream>
#include <set>
#include <climits>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <type_traits>
#include <string>
#include <queue>
#include <map>

using namespace std;
typedef int64_t ll;
const int MOD = 1e9 + 7;
class Graph {
public:
	Graph (int n) {
		adj.resize(n);
	}
	void dfs (int curNode) {
		col[curNode] = cntr;
		for (int i: adj[curNode]) {
			if (col[i] == -1) {
				dfs (i);
			}
		}
	}
	void read() {
		col.assign(adj.size(), -1);
		for (int i = 0; i < adj.size(); i++) {
			if (col[i] == -1) {
				dfs (i);
				cntr++;
			}
		}
	}
	void add_edge (int u, int v)  {
		//cout << u << "<->" << v << '\n';
		adj[u].push_back(v), adj[v].push_back(u);
	}
	vector<vector<int>> adj;
	vector<int> col;
	int cntr = 0;
};
int main() {
	int n;
	cin >> n;
	vector<int> v(n);
	vector<vector<int>> oc(n);
	for (int i = 0; i < n; i++) {
		cin >> v[i];
		v[i]--;
		oc[v[i]].push_back(i);
	}
	map<int,int> myMap;
	for (vector<int>& vec: oc) {
		for (int j: vec) {
			myMap[j] = vec.back();
			//cout << j << "->" << vec.back() << '\n';
		}
	}
	Graph g(n);
	set<int> s;
	int prev = -1;
	for (int i = 0; i < n; i++) {
		g.add_edge(myMap[i], myMap[v[i]]);
	}
	g.read();
	int cc = 0;
	prev = 0;
	vector<int> ans;
	ans.resize(n, -1);
	int K = 100;
	cout << K << '\n';
	for (int i = 0; i < n; i++) {
		if (g.adj[i].empty()) {
			ans[i] = prev;
			continue;
		}
		if (g.col[i] == cc) {
			ans[i] = (prev += K);
		} else {
			ans[i] = (prev += 2 * K);
			cc = g.col[i];
		}
	}
	for (int i = 0; i < ans.size(); i++) {
		ans[i] = ans[myMap[i]];
	}
	for (int i = ans.size() - 1; i >= 0; i--) {
		ans[i] = ans[myMap[i]];
	}
	prev = -1;
	for (auto& i: ans) {
		if (abs(i - prev) < K) {
			i = prev + 1;
		}
		cout << i << ' ';
		prev = i;
	}
}
