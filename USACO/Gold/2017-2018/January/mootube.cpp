#include <vector>
#include <iostream>
#include <cassert>
#include <cmath>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <climits>
#include <unordered_map>
#include <set>
#include <algorithm>
#include <iomanip>
using namespace std;
struct dsu{
    vector<int> parent;
    vector<int> compSize;
    int N;
    void fill(){
        parent.resize(N), compSize.resize(N);
        for(int i = 0; i < N; i++){
            parent[i] = i, compSize[i] = 1;
        }
    }
    int find_head(int x){
        if(x == parent[x]){
            return x;
        }
        return find_head(parent[x]);
    }
    void join(int x, int y){
        x = find_head(x);
        y = find_head(y);
        if(x == y){
            return;
        }
        if(compSize[x] > compSize[y]){
            swap(x,y);
            //ensures that compSize[x1] <= compSize[y1]
        }
        parent[x] = y;
        compSize[y] += compSize[x];
    }
    bool comp(int x, int y){
        return (find_head(x) == find_head(y));
    }
};
int main() {
    freopen("mootube.in", "r", stdin);
    freopen("mootube.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    dsu g;
    cin >> g.N;
    g.fill();
    int Q;
    cin >> Q;
    map<int,vector<pair<int,int>>> myMap;
    set<int> mySet;
    for (int i = 0; i < g.N - 1; i++) {
        int a, b, s;
        cin >> a >> b >> s;
        a--, b--;
        myMap[-s].push_back({a, b});
        mySet.insert(s);
    }
    vector<pair<int,int>> vec(Q);
    map<int,vector<int>> m;
    map<pair<int,int>,int> ans;
    for (int i = 0; i < Q; i++) {
        cin >> vec[i].first >> vec[i].second;
        vec[i].first--, vec[i].second--;
        swap(vec[i].first, vec[i].second);
        if (mySet.upper_bound(vec[i].second) == mySet.end()) {
            auto it = mySet.end();
            it--;
            vec[i].second = *it;
        } else {
            vec[i].second = *mySet.upper_bound(vec[i].second);
        }
        m[vec[i].second].push_back(vec[i].first);
    }
    for (auto p: myMap) {
        vector<pair<int,int>> edges = p.second;
        for (auto q: edges) {
            g.join(q.first, q.second);
        }
        for (int i: m[-p.first]) {
            ans[make_pair(i, -p.first)] = g.compSize[g.find_head(i)];
        }
    }
    for (auto p: vec) {
        cout << ans[p] - 1 << endl;
    }
    //cout << "MISSION IMPOSSIBLE";
}
