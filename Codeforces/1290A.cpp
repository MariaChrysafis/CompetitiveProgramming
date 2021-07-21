#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#define ll long long
using namespace std;
void print(vector<pair<ll, ll>> v){
    for(pair<ll, ll> p: v){
        cout << p.first << " " << p.second << endl;
    }
}
void print(vector<int> v){
    for(int i: v){
        cout << i << " ";
    }
    cout << endl;
}
vector<int> read(int n){
    vector<int> v;
    for(int i = 0; i < n; i++){
        int x;
        cin >> x;
        v.push_back(x);
    }
    return v;
}
int worst(vector<int> v, int ch){
    int pos = 1e9;
    for(int i = 0; i < v.size(); i++){
        int l = i;
        int r = i + v.size() - ch - 1;
        if(r >= v.size()) continue;
        int pot = 0;
        //if(l != 0) pot = v[l - 1];
        //if(r != v.size() - 1) pot = max(pot, v[r + 1]);
        pot = max(v[l], v[r]);
        pos = min(pot, pos);
    }
    return pos;
}
void solve(){
    int n, m, k;
    cin >> n >> m >> k;
    vector<int> v = read(n);
    //cout << worst({13, 60, 4}, 2) << endl;
    k = min(k, m - 1);
    int ans = 0;
    for(int i = 0; i < n; i++){
        //remove k of them
        int l = i;
        int r = i + n - k - 1;
        if(r >= n) break;
        vector<int> vec;
        for(int i = l; i <= r; i++){
            vec.push_back(v[i]);
        }
        //print(vec);
        //cout << worst(vec, m - k - 1) << '\n';
        ans = max(ans, worst(vec, m - k - 1));
    }
    cout << ans << '\n';
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while(t--) {
        solve();
    }
}
