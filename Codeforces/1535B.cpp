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
long long GCD(long long a, long long b){
    if(min(a,b) == 0) return max(a,b);
    return GCD(max(a,b) % min(a,b), min(a,b));
}
void solve(){
    long long n;
    cin >> n;
    vector<long long> arr(n);
    for(int i = 0; i < n; i++) cin >> arr[i];
    vector<long long> arr1;
    for(int i = 0; i < n; i++) if(arr[i] % 2 == 1) arr1.push_back(arr[i]);
    long long cntr = 0;
    for(int i = 0; i < arr1.size(); i++){
        for(int j = i + 1; j < arr1.size(); j++){
            if(GCD(arr1[i], arr1[j]) == 1) cntr++;
        }
    }
    cout << n * (n - 1)/2 - cntr << endl;
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
