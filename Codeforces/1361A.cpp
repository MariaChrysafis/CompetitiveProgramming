#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <map>
#include <set>
using namespace std;
struct Graph{
    vector<vector<int>> adj;
    vector<int> topic;
    void read(){
        int n, m;
        cin >> n >> m;
        adj.resize(n), topic.resize(n);
        map<int,vector<int>> oc;
        for(int i = 0; i < m; i++){
            int u, v;
            cin >> u >> v;
            u--, v--;
            adj[u].push_back(v), adj[v].push_back(u);
        }
        for(int i = 0; i < n; i++){
            cin >> topic[i];
            oc[topic[i]].push_back(i);
        }
        for(int i = 0; i < n; i++){
            for(int j: adj[i]){
                if(topic[j] == topic[i]){
                    cout << -1 << endl;
                    return;
                }
            }
        }
        for(int i = 0; i < n; i++){
            set<int> s;
            for(int j: adj[i]){
                if(topic[j] < topic[i]){
                    s.insert(topic[j]);
                }
            }
            if(s.size() != topic[i] - 1){
                cout << "-1\n";
                return;
            }
        }
        vector<int> ans;
        for(pair<int,vector<int>> p: oc){
            for(int x: p.second){
                ans.push_back(x);
                if(p.first == 1) continue;
                bool fine = false;
                for(int y: adj[x]){
                    if(topic[y] == p.first - 1){
                        fine = true;
                    }
                }
                if(!fine){
                    cout << "-1\n";
                    return;
                }
            }
        }
        for(int i: ans){
            cout << i + 1 << " ";
        }
        cout << endl;
    }
};
int main() {
    Graph g;
    g.read();
}
