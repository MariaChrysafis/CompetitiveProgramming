#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <cmath>
#include <queue>
#include <map>
#include <iomanip>
using namespace std;
void printvii(vector<vector<int>> v) {
	for (int i = 0; i < v.size(); i++) {
		for (int j: v[i]) {
			cout << j << " ";
		}
		cout << endl;
	}
	cout << endl;
}
int n;
struct Graph {
	vector<vector<int>> adj;
	vector<int> toposort() {
		vector<vector<int>> inv_adj(adj.size());
		for (int i = 0; i < adj.size(); i++) {
			for (int j: adj[i]) {
				inv_adj[j].push_back(i);
			}
		}
		vector<int> inDegree(n);
		priority_queue<int, vector<int>, greater<int>> q;
		for (int i = 0; i < adj.size(); i++) {
			inDegree[i] = inv_adj[i].size();
			if (inDegree[i] == 0) {
				q.push(i);
			}
		}
		vector<int> v;
		while (!q.empty()) {
			int x = q.top();
			v.push_back(x);
			q.pop();
			for (int i: adj[x]) {
				inDegree[i]--;
				if (inDegree[i] == 0) {
					q.push(i);
				}
			}
		}
		//reverse(v.begin(), v.end());
		return v;
	}
};
vector<vector<int>> inp;
vector<int> ts (int x) {
	Graph g;
	g.adj.resize(n);
	for (int i = 0; i < x; i++) {
		for (int j = 1; j < inp[i].size(); j++) {
			g.adj[inp[i][j - 1]].push_back(inp[i][j]);
		}
	}
	return g.toposort();
}
bool valid (int x) {
	return (ts(x).size() == n);
}
int binSearch (int l, int r) {
	int m = (l + r + 1)/2;
	if (l == r) {
		assert(valid(l));
		return l;
	}
	if (valid(m)) {
		return binSearch(m, r);
	} else {
		return binSearch(l, m - 1);
	}
}
int main() {
	freopen("milkorder.in", "r", stdin);
	freopen("milkorder.out", "w", stdout);
	int m;
	cin >> n >> m;
	for (int tc = 0; tc < m; tc++) {
		inp.push_back({});
		int x;
		cin >> x;
		for (int i = 0; i < x; i++) {
			int y;
			cin >> y;
			y--;
			inp.back().push_back(y);
		}
	}
	int x = binSearch(0, m);
	vector<int> v = ts(x);
	for (int i = 0; i < v.size(); i++) {
		cout << v[i] + 1;
		if (i != v.size() - 1) cout << ' ';
	}
}

