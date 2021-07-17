#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <set>
#include <map>
 
using namespace std;
struct triple{
    int x, y, z, ind;
};
struct box{
    triple t1, t2;
};
int dist(triple t1, triple t2){
    return abs(t1.x - t2.x) + abs(t1.y - t2.y) + abs(t1.z - t2.z);
}
bool comp(triple t1, triple t2){
    if(t1.x != t2.x) return (t1.x < t2.x);
    if(t1.y != t2.y) return (t1.y < t2.y);
    return (t1.z < t2.z);
}
bool inside(triple t1, box b1){
    int minX = min(b1.t1.x, b1.t2.x);
    int maxX = max(b1.t1.x, b1.t2.x);
    int minY = min(b1.t1.y, b1.t2.y);
    int maxY = max(b1.t1.y, b1.t2.y);
    int minZ = min(b1.t1.z, b1.t2.z);
    int maxZ = max(b1.t1.z, b1.t2.z);
    return (t1.x >= minX && t1.x <= maxX && t1.y >= minY && t1.y <= maxY && t1.z >= minZ && t1.z >= maxZ);
}
struct DAG{
    int n; // number of vertices
    vector<vector<int>> adj; // adjacency list of graph
    vector<bool> visited;
    vector<int> ans;
 
    void dfs(int v) {
        visited[v] = true;
        for (int u : adj[v]) {
            if (!visited[u])
                dfs(u);
        }
        ans.push_back(v);
    }
 
    void topological_sort() {
        n = adj.size();
        visited.assign(n, false);
        ans.clear();
        for (int i = 0; i < n; ++i) {
            if (!visited[i])
                dfs(i);
        }
        reverse(ans.begin(), ans.end());
    }
};
int main() {
    int n;
    cin >> n;
    vector<triple> v(n);
    for(int i = 0; i < n; i++){
        cin >> v[i].x >> v[i].y >> v[i].z;
        v[i].ind = i + 1;
    }
    set<int> s;
    vector<box> boxes;
    for(int i = 0; i < n; i++){
        if(s.count(i)) continue;
        int myMin = 1e9;
        int best = -1;
        for(int j = 0; j < n; j++){
            if(i == j || s.count(j)) continue;
            int x = dist(v[i], v[j]);
            if(x < myMin){
                best = j;
                myMin = x;
            }
        }
        s.insert(best), s.insert(i);
        cout << v[best].ind << " " << v[i].ind << endl;
        boxes.push_back({v[best], v[i]});
    }
    return 0;
    //cout << endl;
    vector<vector<int>> adj(boxes.size());
    for(int i = 0; i < boxes.size(); i++){
        for(int j = 0; j < boxes.size(); j++){
            if(j == i) continue;
            if(inside(boxes[i].t1, boxes[j]) || inside(boxes[i].t2, boxes[j])){
                adj[i].push_back(j);
            }
        }
    }
    DAG graph;
    graph.adj = adj;
    graph.topological_sort();
    for(int i = 0; i < graph.ans.size(); i++){
        cout << boxes[graph.ans[i]].t1.ind << " " << boxes[graph.ans[i]].t2.ind << endl;
    }
 
}
