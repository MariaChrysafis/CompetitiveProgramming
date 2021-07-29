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
#include <array>
#include <iomanip>
 
#define ll long long
#define endl '\n'
 
using namespace std;
void print(vector<int> v){
    for(int i : v) cout << i << " ";
    cout << endl;
}
void print(vector<ll> v){
    for(ll i : v) cout << i << " ";
    cout << endl;
}
void print(vector<vector<int>> v){
    for(vector<int> vec: v) print(vec);
    cout << endl;
}
void print(vector<vector<ll>> v){
    for(vector<ll> vec: v) print(vec);
    cout << endl;
}
ll n, m;
vector<ll> pos;
vector<ll> powr;
ll construct(ll y){
    ll x = 0;
    for(int i = 0; i < pos.size(); i++){
        if(y & powr[i]){
            x += (1 << pos[i]);
        }
    }
    return x;
}
bool valid(ll x){
    //can we produce x
    return ((n ^ x) <= m);
}
ll binSearch(ll l, ll r){
    ll mid = (l + r + 1)/2;
    if(l == r){
        return l;
    }
    if(valid(construct(mid))){
        return binSearch(mid, r);
    }else{
        return binSearch(l, mid - 1);
    }
}
void solve(){
    cin >> n >> m;
    if(n > m){
        cout << 0 << endl;
        return;
    }
    pos.clear();
    for(int i = 0; i <= 30; i++){
        if(!(n & powr[i])){
            pos.push_back(i);
        }
    }
    sort(pos.begin(), pos.end());
    cout << construct(binSearch(0, powr[pos.size()]) + 1) << endl;
}
 
int main() {
    powr.push_back(1);
    while(powr.size() != 32){
        powr.push_back(powr.back() * 2);
    }
    int t;
    cin >> t;
    while(t--){
        solve();
    }
}
