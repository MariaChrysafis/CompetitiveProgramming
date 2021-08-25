#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <cmath>
#include <set>
#define ll long long
using namespace std;
void print(vector<int> v){
    for(int i: v) cout << i << " ";
    cout << endl;
}
int find_index(vector<int> v, int val){
    for(int i = 0; i < v.size(); i++){
        if(v[i] == val){
            return i;
        }
    }
    return -1;
}
vector<int> reverse(vector<int> v, int pref){
    cout << pref + 1 << " ";
    reverse(v.begin(), v.begin() + pref + 1);
    return v;
}
int n, m, q;
void solve(){
    cin >> n >> m >> q;
    vector<pair<int,int>> inp(m);
    map<int,int> myMap;
    for(int i = 0; i < m; i++){
        cin >> inp[i].first >> inp[i].second;
        myMap[inp[i].first] = max(myMap[inp[i].first], inp[i].second);
    }
    sort(inp.begin(), inp.end());
    vector<pair<int,int>> v;
    for(int i = 1; i <= n; i++){
        //if(myMap[i] == 0) continue;
        v.push_back({i, myMap[i]});
    }
    vector<int> rng_max;
    rng_max.push_back(0);
    for(int i = 0; i < v.size(); i++){
        rng_max.push_back(max(rng_max.back(), v[i].second));
    }
    while(q--){
        int u, v;
        cin >> u >> v;
        if(u > v) swap(u, v);
        if(rng_max[u] >= v){
            cout << "Yes\n";
        }else{
            cout << "No\n";
        }
    }
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
}
