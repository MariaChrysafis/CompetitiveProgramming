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
vector<long long> slv(vector<long long> arr){
    for(int i = 0; i < arr.size(); i++){
        long long sum = 0;
        long long cntr = 0;
        for(int j = 0; j <= i; j++){
            if(arr[j] != -1) sum += arr[j], cntr++;
        }
        for(int j = 0; j <= i; j++){
            if(arr[j] != -1 && arr[j] * cntr > sum){
                arr[j] = -1;
            }
        }
    }
    return arr;
}
void solve(){
    int n;
    cin >> n;
    vector<long long> arr(n);
    for(int i = 0; i < n; i++){
        cin >> arr[i];
    }
    int t = sqrt(n);
    while(t--) {
        arr = slv(arr);
        reverse(arr.begin(), arr.end());
        arr = slv(arr);
    }
    int ans = 0;
    for(int i: arr){
        if(i == -1) ans++;
    }
    cout << ans << endl;
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
