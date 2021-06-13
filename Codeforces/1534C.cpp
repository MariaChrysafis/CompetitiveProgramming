#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <array>
#include <stack>
#include <map>
using namespace std;
const int MOD = 1000000007;
void print(vector<int> v){
    for(int i = 0; i < v.size(); i++){
        cout << v[i] << " ";
    }
    cout << endl;
}
long long cost(vector<long long> v){
    long long cntr = v[0] + v[v.size() - 1];
    for(int i = 1; i < v.size(); i++){
        cntr += abs(v[i] - v[i - 1]);
    }
    return cntr;
}
long long change(vector<long long> v1, vector<long long> v2){
    long long cntr = 0;
    for(int i = 0; i < v1.size(); i++){
        cntr += abs(v1[i] - v2[i]);
    }
    return cntr;
}
map<int,vector<int>> adj;
vector<int> cntr;
void dfs(int compN, int u){
    for(int i: adj[u]){
        if(cntr[i] != 0) continue;
        cntr[i] = compN;
        dfs(compN, i);
    }
}
vector<int> pwr;
void solve(){
    adj.clear();
    int n;
    cin >> n;
    cntr.resize(n);
    int arr[2][n];
    for(int i = 0; i < n; i++){
        cin >> arr[0][i];
        arr[0][i]--;
        cntr[i] = 0;
    }
    for(int i = 0; i < n; i++){
        cin >> arr[1][i];
        arr[1][i]--;
    }
    for(int i = 0; i < n; i++){
        adj[arr[0][i]].push_back(arr[1][i]);
    }
    int x = 1;
    for(int i = 0; i < n; i++){
        if(cntr[i] != 0) continue;
        dfs(x, i);
        x++;
    }
    cout << pwr[x - 1] << endl;
}
int main(){
    pwr.resize(400004);
    pwr[0] = 1;
    for(int i = 1; i < pwr.size(); i++){
        pwr[i] = pwr[i - 1] * 2;
        pwr[i] %= MOD;
    }
    int t;
    cin >> t;
    while(t--){
        solve();
    }
}
