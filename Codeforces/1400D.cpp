#include <iostream>
#include <vector>
#include <map>
#include <cassert>
#include <set>
#include <unordered_set>
#include <algorithm>
#include <random>
#include <chrono>
#include <queue>
 
#define ll long long
 
using namespace std;
void print(vector<int> v){
    for(int i: v) cout << i << " ";
    cout << endl;
}
vector<int> v;
int oc(int z, int x1, int y1){
    int cntr = 0;
    for(int i = x1; i <= y1; i++){
        if(v[i] == z){
            cntr++;
        }
    }
    return cntr;
}
void solve(){
    int n;
    cin >> n;
    v.resize(n);
    for(int i = 0; i < n; i++){
        cin >> v[i];
    }
    vector<vector<long long>> pref(n + 1);
    for(int i = 1; i <= n; i++){
        pref[i].resize(n);
        pref[i][0] = (v[0] == i);
        for(int j = 1; j < n; j++){
            pref[i][j] = pref[i][j - 1] + (v[j] == i);
        }
    }
    vector<vector<long long>> suf(n + 1);
    for(int i = 1; i <= n; i++){
        suf[i].resize(n);
        suf[i][0] = pref[i][n - 1];
        for(int j = 1; j < n; j++){
            suf[i][j] = pref[i][n - 1] - pref[i][j - 1];
        }
    }
    long long ans = 0;
    for(int j = 1; j < n; j++){
        for(int k = j + 1; k < n - 1; k++){
            //cout << j << " " << k << " " << pref[v[j]][j - 1] << " " << suf[v[k]][k + 1] << endl;
            ans += pref[v[k]][j - 1] * suf[v[j]][k + 1];
        }
    }
    cout << ans << endl;
}
int main(){
    int t;
    cin >> t;
    while(t--){
        solve();
    }
}
