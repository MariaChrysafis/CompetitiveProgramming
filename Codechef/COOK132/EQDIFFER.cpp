#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <cmath>
#include <set>
#include <queue>

#define ll long long
using namespace std;
#define P(x, y) make_pair(x,y)
using namespace std;
void print(vector<int> v){
    for(int i: v) cout << i << " ";
    cout << endl;
}
void solve(){
    int n;
    cin >> n;
    vector<int> v(n);
    map<int,int> oc;
    for(int i = 0; i < n; i++){
        cin >> v[i];
        oc[v[i]]++;
    }
    int op1 = min(2, n);
    for(pair<int,int> p: oc){
        op1 = max(op1, p.second);
    }
    cout << n - op1 << endl;
}
int main() {
    int t;
    cin >> t;
    while(t--){
        solve();
    }
}
