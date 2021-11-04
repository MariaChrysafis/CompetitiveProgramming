#include <iostream>
#include <queue>
#include <vector>
#include <map>
#define pb push_back
using namespace std;
map<int,vector<int>> adj;
int deg[200000];
bool flag[200000];
int main(){
    int n,m;
    cin >> n >> m;
    for(int i = 0; i < m; i++){
        int a,b;
        cin >> a >> b;
        adj[a - 1].pb(b - 1);
        adj[b - 1].pb(a - 1);
        deg[b - 1]++;
    }
    //Topological Sort
    vector<int> v;
    priority_queue<int> pq;
    for(int i = 0; i < n; i++){
        if(deg[i] == 0){
            pq.push(i);
        }
    }
    while(!pq.empty()){
        while(flag[pq.top()] == true){
            pq.pop();
        }
        int i = pq.top();
        pq.pop();
        if(deg[i] == 0 && flag[i] == false){
            flag[i] = true;
            v.pb(i);
            for(int j: adj[i]){
                deg[j]--;
                if(deg[j] == 0) pq.push(j);
            }
        }
    }
    if(v.size() != n){cout << "IMPOSSIBLE" << endl; return 0;}
    for(int i: v) cout << i + 1 << " ";
    
}
