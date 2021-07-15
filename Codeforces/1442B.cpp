#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <map>
#include <set>
using namespace std;
vector<int> a, b;
const int MOD = 998244353;
void print(vector<int> v){
    for(int i: v) cout << i << " ";
    cout << endl;
}
void solve(){
    int n, k;
    cin >> n >> k;
    a.resize(n + 2);
    map<int,int> oc;
    for(int i = 1; i <= n; i++){
        cin >> a[i];
        oc[a[i]] = i;
        a[i] = i;
    }
    a[n + 1] = 0;
    b.resize(k);
    for(int i = 0; i < k; i++){
        cin >> b[i];
        b[i] = oc[b[i]];
        a[b[i]] *= -1;
    }
    long long ans = 1;
    for(int i = 0; i < k; i++){
        ans *= (a[b[i] - 1] > 0) + (a[b[i] + 1] > 0);
        ans %= MOD;
        a[b[i]] *= -1;
    }
    cout << ans << endl;
}
int main() {
    int t;
    cin >> t;
    while(t--){
        solve();
    }
}
