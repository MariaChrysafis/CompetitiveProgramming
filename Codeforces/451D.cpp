#include <iostream>
#include <vector>
#include <cmath>
#include <queue>
#include <set>
 
#define ll long long
using namespace std;
 
void print(vector<ll> v){
    for(ll x: v) cout << x << " ";
    cout << '\n';
}
 
void print(vector<int> v){
    for(int x: v) cout << x << " ";
    cout << '\n';
}
 
void solve(){
    string s;
    cin >> s;
    vector<int> a[2], b[2];
    for(int i = 0; i < s.length(); i++){
        if(s[i] == 'a') {
            a[i % 2].push_back(i);
        } else {
            b[i % 2].push_back(i);
        }
    }
    ll odd = 0;
    for(int i = 0; i < 2; i++){
        ll x = b[i].size();
        ll y = a[i].size();
        odd += x * (x + 1)/2;
        odd += y * (y + 1)/2;
    }
    ll even = 0;
    even += (b[0].size() * b[1].size());
    even += (a[0].size() * a[1].size());
    cout << even << " " << odd << endl;
 
}
 
int main() {
    int t = 1;
    while(t--){
        solve();
    }
}
