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
#include <unordered_map>

using namespace std;

struct Graph {
    vector<vector<int>> adj;
    map<pair<int,int>,int> myMap;

    Graph (int N) {
        adj.resize(N);
    }

    void add_edge (int u, int v) {
        adj[u].push_back(v), adj[v].push_back(u);
        myMap[{u, v}] = myMap[{v, u}] = true;
    }

    bool isOkay (vector<int> v) {
        sort(v.begin(), v.end());
        for (int i = 1; i < v.size(); i++) {
            if (v[i] == v[i - 1]) {
                return false;
            }
        }
        set<bool> s;
        for (int i: v) {
            for (int j: v) {
                if (i != j) {
                    //cout << i << " " << j << " " << myMap[{i, j}] << '\n';
                    s.insert(myMap[{i, j}]);
                }
            }
        }
        //cout << s.size() << '\n';
        return (s.size() == 1);
    }

    bool test () {
        if (adj.size() <= 40) {
            for (int i1 = 0; i1 < adj.size(); i1++) {
                for (int i2 = i1 + 1; i2 < adj.size(); i2++) {
                    for (int i3 = i2 + 1; i3 < adj.size(); i3++) {
                        for (int i4 = i3 + 1; i4 < adj.size(); i4++) {
                            for (int i5 = i4 + 1; i5 < adj.size(); i5++) {
                                //cout << i1 << " " << i2 << " " << i3 << " " << i4 << " " << i5 << '\n';
                                if (isOkay({i1, i2, i3, i4, i5})) {
                                    cout << i1 + 1 << " " << i2 + 1 << " " << i3 + 1<< " " << i4 + 1 << " " << i5 + 1<< '\n';
                                    return true;
                                }
                            }
                        }
                    }
                }
            }
            cout << "-1\n";
            return false;
        }
        int q = 100000;
        while (q--) {
            vector<int> v(5);
            for (int i = 0; i < 5; i++) {
                v[i] = rand() % adj.size();
            }
            if (isOkay(v)) {
                for (int i: v) cout << i + 1 << ' ';
                cout << '\n';
                return false;
            }
        }
        cout << "-1\n";
        return true;
    }
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int N, M;
    cin >> N >> M;
    Graph g(N);
    while (M--) {
        int u, v; cin >> u >> v; u--, v--;
        g.add_edge(u, v);
    }
    g.test();

}
