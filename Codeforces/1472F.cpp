#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <queue>
#include <set>
#include <stack>
#include <map>
#define ll long long
using namespace std;
void print(vector<int> v){
    for(int i: v) cout << i << " ";
    cout << endl;
}
 
bool solve(){
    int n, m;
    cin >> n >> m;
    vector<pair<int,int>> v(m);
    for(int i = 0; i < m; i++){
        cin >> v[i].second >> v[i].first;
    }
    if(m % 2 == 1){
        return false;
    }
    sort(v.begin(), v.end());
    for(int i = 0; i < m - 1; i += 2){
        if(v[i].second == v[i + 1].second && (v[i + 1].first - v[i].first) % 2 == 0){
            return false;
        }
        if(v[i].second != v[i + 1].second && (v[i + 1].first - v[i].first) % 2 == 1){
            return false;
        }
        if(v[i + 1].first == v[i + 2].first){
            return false;
        }
    }
    return true;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin >> t;
    while(t--){
        bool b = solve();
        if(b) cout << "YES\n";
        else cout << "NO\n";
    }
 
}
