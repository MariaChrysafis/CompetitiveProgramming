#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <iomanip>
#include <string>
#include <array>
#include <cassert>
#include <algorithm>
using namespace std;
bool comp(pair<int,int> p1, pair<int,int> p2){
    if(p1.first < p2.first) return true;
    else if(p1.first > p2.first) return false;
    return (p1.second > p2.second);
}
vector<vector<int>> adj;
vector<int> type; //1 -> leaf , 2 --> bud
int dfs(int curNode, int prevNode){
    bool allBuds = true;
    for (int i: adj[curNode]){
        if(i == prevNode) continue;
        int x = dfs(i, curNode);
        if(x == 1){
            //this means that it's a leaf
            allBuds = false;
        }
    }
    if(allBuds){
        return type[curNode] = 1;
    } else {
        return type[curNode] = 2;
    }
}
void solve(){
    adj.clear();
    int n;
    cin >> n;
    adj.resize(n);
    type.resize(n);
    for(int i = 0; i < n - 1; i++){
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v), adj[v].push_back(u);
    }
    dfs(0, -1);
    int cntr = 0;
    type[0] = 0;
    bool rl = false;
    for(int i: adj[0]){
        if(type[i] == 1){
            rl = true;
        }
    }
    for(int i: type) {
        cntr += (i == 2);
    }
    cout << n - 2 * cntr - rl << endl;

}
int main(){
    int t;
    cin >> t;
    while(t--) {
        solve();
    }
}
