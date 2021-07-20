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
void solve() {
    int n;
    cin >> n;
    vector<pair<ll, ll>> v(n);
    ll myMin = 1e12;
    for(int i = 0; i < n; i++){
        cin >> v[i].first >> v[i].second;
    }
    for(int i = 0; i < n; i++){
        int nxt = (i + 1) % n;
        ll val = v[nxt].first - max(v[nxt].first - v[i].second, 0ll);
        myMin = min(val, myMin);
    }
    int ind = 0;
    for(int i = 0; i < n; i++){
        int nxt = (i + 1) % n;
        ll val = v[nxt].first - max(v[nxt].first - v[i].second, 0ll);
        if(val == myMin){
            ind = i;
            break;
        }
    }
    ind += n;
    ind++;
    ind %= n;
    rotate(v.begin(), v.begin() + ind, v.end());
    bool killed[n];
    for(int i = 0; i < n; i++) killed[i] = false;
    ll moves = 0;
    for(int i = 0; i < n; i++){
        moves += v[i].first;
        v[i].first = 0;
        int nxt = (i + 1) % n;
        if(v[nxt].first > v[i].second){
            v[nxt].first -= v[i].second;
            continue;
        }
        v[nxt].first = 0;
    }
    cout << moves << '\n';
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
