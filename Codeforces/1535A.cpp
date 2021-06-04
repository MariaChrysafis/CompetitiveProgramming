#include <bitset>
#include <iostream>
#include <vector>
#include <cmath>
#include <unordered_map>
#include <chrono>
#include <algorithm>
#include <map>
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
using namespace std;
vector<int> v;
int better(int ind1, int ind2){
    if(v[ind1] < v[ind2]){
        return ind2;
    }else{
        return ind1;
    }
}
pair<int,int> solve(vector<int> arr){
    if(arr.size() == 4){
        return solve({better(arr[0], arr[1]), better(arr[2], arr[3])});
    }
    if(arr.size() == 2){
        return {arr[0], arr[1]};
    }
}
void solve(){
    v.resize(4);
    cin >> v[0] >> v[1] >> v[2] >> v[3];
    vector<pair<int,int>> vp(4);
    for(int i = 0; i < 4; i++){
        vp[i] = {v[i], i};
    }
    sort(vp.begin(), vp.end());
    pair<int,int> p = solve({0,1,2,3});
    if(vp[2].second != p.first && vp[2].second != p.second){
        cout << "NO" << endl;
        return;
    }
    if(vp[3].second != p.first && vp[3].second != p.second){
        cout << "NO" << endl;
        return;
    }
    cout << "YES" << endl;
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while(t--){
        solve();
    }
}
