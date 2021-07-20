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
void solve(){
    ll q;
    cin >> q;
    ll x;
    cin >> x;
    set<ll> v;
    int arr[x];
    for(int i = 0; i < x; i++){
        arr[i] = i - x; //the last thing we put that is i modulo x
    }
    int prev = 0;
    while(q--){
        ll val;
        cin >> val;
        v.insert(arr[val % x] + x);
        arr[val % x] += x;
        while(v.count(prev)){
            prev++;
        }
        //print(v);
        cout << prev << endl;
    }
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
}
