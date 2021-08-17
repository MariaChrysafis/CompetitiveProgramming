#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <map>
 
#define ll long long
using namespace std;
void print(vector<int> v){
    for(int x: v) cout << x << " ";
    cout << endl;
}
 
void print(vector<ll> v){
    for(ll x: v) cout << x << " ";
    cout << endl;
}
 
int findMax(vector<int> v){
    int myMax = 0;
    for(int i = 0; i < v.size(); i++){
        myMax = max(myMax, v[i]);
    }
    return myMax;
}
void solve(){
    int n;
    cin >> n;
    vector<int> v(n + 1);
    for(int i = 1; i <= n; i++){
        cin >> v[i];
    }
    int cur = v[n];
    for(int i = n - 1; i >= 1; i--){
        cur = cur & v[i];
    }
    cout << cur << endl;
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while(t--){
        solve();
    }
}
