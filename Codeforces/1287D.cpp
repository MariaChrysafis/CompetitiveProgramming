/**
 * code generated by JHelper
 * More info: https://github.com/AlexeyDmitriev/JHelper
 * @author Maria Chrysafis (Olympia)
 */



#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <iomanip>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <string>
#include <random>
using namespace std;
class DNumbersOnTree {
public:
    struct Graph {
        vector<vector<int>> adj;
        vector<int> c;
        vector<int> ans;
        vector<int> sub;
        int find_val (int x) {
            int cntr = 0;
            for (int i = 1; i < adj.size(); i++) {
                if (ans[i] != -1) {
                    continue;
                }
                if (cntr == x) {
                    return i;
                }
                cntr++;
            }
            return -1;
        }
        void dfs (int curNode) {
            int x = find_val(c[curNode]);
            ans[x] = curNode;
            for (int i: adj[curNode]) {
                dfs (i);
            }
        }
        int dfs1 (int curNode) {
            sub[curNode] = 1;
            for (int i: adj[curNode]) {
                sub[curNode] += dfs1(i);
            }
            return sub[curNode];
        }
    };
	void solve(std::istream& in, std::ostream& out) {
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);
        Graph g;
        int n;
        in >> n;
        g.adj.resize(n + 1);
        g.c.resize(n + 1);
        g.ans.assign(n + 1, -1);
        g.sub.assign(n + 1, 0);
        int root = 0;
        for (int i = 1; i <= n; i++) {
            int parent, x;
            in >> parent >> x;
            g.c[i] = x;
            if (parent == 0) {
                root = i;
            }
            g.adj[parent].push_back(i);
        }
        g.dfs1(root);
        for (int i = 1; i <= n; i++) {
            if (g.sub[i] <= g.c[i]) {
                out << "NO\n";
                return;
            }
        }
        g.dfs(root);
        int ans[n + 1];
        for (int i = 0; i < g.ans.size(); i++) {
            ans[g.ans[i]] = i;
        }
        out << "YES\n";
        for (int i = 1; i <= n; i++) {
            out << ans[i] << ' ';
        }
        out << '\n';
	}
};


int main() {
	DNumbersOnTree solver;
	std::istream& in(std::cin);
	std::ostream& out(std::cout);
	solver.solve(in, out);
	return 0;
}
