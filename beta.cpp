#include <cmath>
#include <iostream>
#include <set>
#include <climits>
#include <cstdio>
#include <algorithm>
#include <cassert>
#include <string>
#include <vector>
#include <iomanip>
#include <unordered_map>
#include <type_traits>
#include <string>
#include <queue>
#define ll int
#include <map>

using namespace std;
struct Tree{
    vector<vector<int>> adj;
    vector<int> last, first;
    vector<int> euler;
    int counter = 0;
    void pre_euler(){
        euler.resize( 2 * adj.size()), first.resize(adj.size()), last.resize(adj.size());
        dfs(0, -1, 0);
        for (int i = 0; i < adj.size(); i++) {
            euler[first[i]] = i;
            euler[last[i]] = i;
        }
    }
    void dfs(int node, int parent, int h){
        first[node] = counter++;
        for(int i: adj[node]){
            if(i != parent){
                dfs(i, node, h + 1);
            }
        }
        last[node] = counter++;
    }
};
map<int,set<pair<int,int>>> myMap; //map an integer to which integers have that thing
vector<int> colorfullness;
int main() {
    freopen("snowcow.in", "r", stdin);
    freopen("snowcow.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N, Q;
    cin >> N >> Q;
    Tree t;
    t.adj.resize(N);
    colorfullness.assign(2 * N, 0);
    for (int i = 0; i < N - 1; i++) {
        int u, v;
        cin >> u >> v;
        t.adj[--u].push_back(--v);
        t.adj[v].push_back(u);
    }
    t.pre_euler();
    while (Q--) {
        int dum;
        cin >> dum;
        if (dum == 1) {
            int x, c;
            cin >> x >> c;
            x--;
            vector<pair<int,int>> removal;
            bool fine = true;
            for (pair<int,int> p: myMap[c]) {
                if (p.first <= t.first[x] && p.second >= t.last[x]) {
                    fine = false;
                }
            }
            if (!fine) {
                continue;
            }
            for (pair<int,int> p: myMap[c]) {
                if (p.first > t.first[x] && p.second < t.last[x]) {
                    removal.push_back(p);
                }
            }
            for (auto p: removal) {
                for (int i = p.first; i <= p.second; i++) {
                    colorfullness[i]--;
                }
                myMap[c].erase(p);
            }
            for (int i = t.first[x]; i <= t.last[x]; i++) {
                colorfullness[i]++;
            }
            myMap[c].insert({t.first[x], t.last[x]});
        } else {
            int x;
            cin >> x;
            x--;
            int ans = 0;
            for (int j = t.first[x]; j <= t.last[x]; j++) {
                ans += colorfullness[j];
            }
            cout << ans/2 << '\n';
        }
    }
}
