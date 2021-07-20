#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
using namespace std;
long long MOD = 1e9 + 7;
vector<long long> fact;
 
void solve() {
    int n, k;
    cin >> n >> k;
    int h[n];
    for(int i = 0; i < n; i++){
        cin >> h[i];
    }
    int dpMin[n];
    int dpMax[n];
    dpMin[0] = dpMax[0] = h[0];
    for(int i = 1; i < n; i++){
        dpMin[i] = dpMin[i - 1] - k + 1;
        if(dpMin[i] < h[i]) dpMin[i] = h[i];
        dpMax[i] = dpMax[i - 1] + k - 1;
        if(dpMax[i] > h[i] + k - 1) dpMax[i] = h[i] + k - 1;
        if(dpMax[i] < dpMin[i]){
            cout << "NO\n";
            return;
        }
    }
    if(h[n - 1] > dpMax[n - 1] || h[n - 1] < dpMin[n - 1]){
        cout << "NO\n";
        return;
    }
    cout << "YES\n";
}
int main(){
    int t;
    cin >> t;
    while(t--){
        solve();
    }
}
