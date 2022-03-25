#include <vector>
#include <algorithm>
#include <iostream>
#include <set>
#include <cmath>
#include <map>
#include <random>
#include <cassert>
#include <ctime>
#include <cstdlib>
#include <queue>
#include <limits.h>
using namespace std;

bool pq (int64_t x) {
    int y = sqrt(x);
    if (y * y == x) return true;
    if ((y + 1) * (y + 1) == x) return true;
    return false;
}

struct graph{
    vector<vector<pair<int,int>>> adj; //{-weight, node}
    vector<int> dijk(int src){
        vector<int> dist;
        vector<bool> mark;
        dist.resize(adj.size()), mark.resize(adj.size());
        for(int i = 0; i < adj.size(); i++){
            dist[i] = 1e9;
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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        int64_t n, B, x, y;
        cin >> n >> B >> x >> y;
        n++;
        vector<int64_t> a(n);
        a[0] = 0;
        for (int i = 1; i < n; i++) {
            a[i] = a[i - 1] + x;
            if (a[i] <= B) {
                continue;
            }
            a[i] = a[i - 1] - y;
        }
        int64_t ans = 0;
        for (int i: a) {
            ans += i;
        }
        cout << ans << '\n';
    }
}
