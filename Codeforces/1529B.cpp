#include <bitset>
#include <iostream>
#include <vector>
#include <cmath>
#include <unordered_map>
#include <chrono>
#include <algorithm>
#include <map>
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
using namespace std;
void solve(){
    int n;
    cin >> n;
    vector<long long> arr(n);
    for(int i = 0; i < n; i++){
        cin >> arr[i];
    }
    if(n == 1){
        cout << 1 << endl;
        return;
    }
    int cntr = 0;
    vector<int> v;
    for(int i = 0; i < n; i++) if(arr[i] <= 0) cntr++, v.push_back(arr[i]);
    sort(v.begin(), v.end());
    if(v.size() == 0){
        cout << 1 << endl;
        return;
    }
    //return;
    vector<int> dif;
    for(int i = 0; i < v.size() - 1; i++){
        dif.push_back(abs(v[i] - v[i + 1]));
    }
    sort(dif.begin(), dif.end());
    bool val = false;
    for(int i = 0; i < n; i++){
        if(dif.size() == 0 || (dif[0] >= arr[i] && arr[i] > 0)){
            val = true;
        }
    }
    cout << cntr + val << endl;
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
