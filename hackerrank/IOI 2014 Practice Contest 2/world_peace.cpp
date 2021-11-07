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
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    dsu g;
    cin >> g.N;
    g.fill();
    int M;
    cin >> M;
    map<int,vector<pair<int,int>>> myMap;
    for (int i = 0; i < M; i++) {
        int a, b, s;
        cin >> a >> b >> s;
        a--, b--;
        myMap[s].push_back({a, b});
    }
    int P;
    cin >> P;
    vector<pair<int,int>> vec(P);
    for (int i = 0; i < P; i++) {
        cin >> vec[i].first >> vec[i].second;
        vec[i].first--, vec[i].second--;
    }
    int cur = 0;
    for (auto p: myMap) {
        vector<pair<int,int>> edges = p.second;
        for (auto q: edges) {
            g.join(q.first, q.second);
        }
        while (cur != vec.size() && g.find_head(vec[cur].first) == g.find_head(vec[cur].second)) {
            cur++;
        }
        if (cur == vec.size()) {
            cout << p.first;
            return 0;
        }
    }
    cout << "MISSION IMPOSSIBLE";
}
