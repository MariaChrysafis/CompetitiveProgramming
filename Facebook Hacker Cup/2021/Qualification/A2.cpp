#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <map>
using namespace std;
const int INF = 1e9;
void print(vector<int> v){
    for(int i: v) cout << i << " ";
    cout << endl;
}
struct Graph{
    vector<vector<int>> adj;
    vector<int> bfs(int x){
        queue<pair<int,int>> q;
        vector<int> hasVisited(adj.size());
        vector<int> shortest_distance(adj.size());
        for(int i = 0; i < shortest_distance.size(); i++){
            shortest_distance[i] = INF;
        }
        q.push({x, 0});
        while(!q.empty()){
            pair<int,int> p = q.front();
            shortest_distance[p.first] = min(p.second, shortest_distance[p.first]);
            hasVisited[p.first] = true;
            q.pop();
            for(int i: adj[p.first]){
                if(hasVisited[i]) continue;
                q.push({i, p.second + 1});
            }
        }
        return shortest_distance;
    }
};
void solve(){
    string s;
    cin >> s;
    Graph g;
    int q;
    cin >> q;
    g.adj.resize(26);
    while(q--){
        string str;
        cin >> str;
        int a = str[0] - 'A';
        int b = str[1] - 'A';
        //cout << a << " " << b << endl;
        g.adj[a].push_back(b);
    }
    vector<vector<int>> shortest_distance(26);
    for(int i = 0; i < 26; i++){
        shortest_distance[i] = g.bfs(i);
    }
    int myMin = 1e9;
    for(char c = 'A'; c <= 'Z'; c++){
        int cntr = 0;
        for(int i = 0; i < s.length(); i++){
            int dist = shortest_distance[s[i] - 'A'][c - 'A'];
            if(dist == INF) {
                cntr = INF;
                break;
            }
            cntr += dist;
        }
        //cout << cntr << " ";
        myMin = min(myMin, cntr);
    }
    if(myMin == INF) myMin = -1;
    cout << myMin;
}
int main(){
    int t;
    cin >> t;
    for(int i = 0; i < t; i++){
        cout << "Case #" << i + 1 << ": ";
        solve();
        if(i != t - 1){
            cout << "\n";
        }
    }
}
