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
 
int cost(string s){
    int cntr = 0;
    for(int i = 1; i < s.length(); i++){
        if(s[i] == s[i - 1]){
            cntr++;
        }
    }
    return cntr;
}
 
const int INF = 1e9;
void solve(){
    int n;
    cin >> n;
    vector<int> v(n + 1);
    for(int i = 1; i <= n; i++){
        cin >> v[i];
    }
    for(int i = 1; i <= n; i++){
        if(v[i] == 0 && v[i + 1] == 1){
            for(int j = 1; j <= i; j++){
                cout << j << " ";
            }
            cout << n + 1 << " ";
            for(int j = i + 1; j <= n; j++){
                cout << j << " ";
            }
            cout << endl;
            return;
        }
    }
    if(v[1] == 1){
        cout << n + 1 << " ";
        for(int i = 1; i <= n; i++){
            cout << i << " ";
        }
        cout << endl;
        return;
    }
    if(v.back() == 0){
        for(int i = 1; i <= n + 1; i++){
            cout << i << " ";
        }
        cout << endl;
        return;
    }
    cout << "-1\n";
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
