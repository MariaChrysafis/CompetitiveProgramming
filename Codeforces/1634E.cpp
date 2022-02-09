#include <cmath>
#include <cassert>
#include <iostream>
#include <set>
#include <climits>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <type_traits>
#include <list>
#include <string>
#include <queue>
#include <map>
#include <stack>
#include <unordered_map>

using namespace std;

class Graph {
public:
    vector<multiset<int>> adj;
    map<int, int> myMap, inv_myMap;
    int cntr = 0;

    Graph(int n) {
        adj.resize(n);
    }

    void add_edge(int u, int v) {
        if (!myMap[u]) {
            myMap[u] = ++cntr;
            inv_myMap[myMap[u]] = u;
            //cout << u << " " << myMap[u] << '\n';
        }
        if (!myMap[v]) {
            myMap[v] = ++cntr;
            inv_myMap[myMap[v]] = v;
            //cout << v << " " << myMap[v] << '\n';
        }
        //cout << inv_myMap[myMap[u]] << " " << inv_myMap[myMap[v]] << '\n';
        //cout << myMap[u] << " " << myMap[v] << '\n';
        adj[myMap[u]].insert(myMap[v]);
        adj[myMap[v]].insert(myMap[u]);
    }
    vector<int> euler() {
        for (int i = 1; i < adj.size(); i++) {
            if (adj[i].size() % 2) {
                //cout << inv_myMap[i] << " " << adj[i].size() << '\n';
                cout << "NO\n";
                exit(0);
            }
        }
        vector<int> res;
        for (int i = 0; i < adj.size(); i++) {
            if (adj[i].size()) {
                //cout << "DO " << i << '\n';
                stack<int> st;
                st.push(i);
                while (st.size()) {
                    int u = st.top();
                    if (adj[u].empty()) {
                        res.push_back(u);
                        st.pop();
                    } else {
                        int v = *adj[u].begin();
                        adj[u].erase(adj[u].find(v));
                        adj[v].erase(adj[v].find(u));
                        st.push(v);
                    }
                }
            }
        }
        return res;
    }


};

const int MAX = 3e5 + 5;

void compress (vector<vector<int>> &v) {
    set<int> s;
    for (auto& vec: v) {
        for (int i: vec) {
            s.insert(i);
        }
    }
    map<int,int> m;
    int cntr = 0;
    for (int i: s) {
        m[i] = cntr++;
    }
    for (int i = 0; i < v.size(); i++) {
        for (int j = 0; j < v[i].size(); j++) {
            v[i][j] = m[v[i][j]];
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    Graph g(MAX + 1);
    vector<vector<int>> arr(t);
    for (int tc = 0; tc < t; tc++) {
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            int x;
            cin >> x;
            arr[tc].push_back(x);
        }
    }
    compress(arr);
    for (int tc = 0; tc < t; tc++) {
        for (int x: arr[tc]) {
            g.add_edge(x, tc + MAX);
        }
    }
    vector<int> v = g.euler();
    map<int,int> myMap[g.adj.size()];
    for (int i = 1; i < v.size(); i++) {
        if (g.inv_myMap[v[i - 1]] >= MAX) {
            myMap[g.inv_myMap[v[i - 1]] - MAX][g.inv_myMap[v[i]]]++;
        }
    }
    cout << "YES\n";
    for (int i = 0; i < arr.size(); i++) {
        for (int j = 0; j < arr[i].size(); j++) {
            if (myMap[i][arr[i][j]] != 0) {
                myMap[i][arr[i][j]]--;
                cout << 'L';
            } else {
                cout << 'R';
            }
        }
        cout << '\n';
    }
}
