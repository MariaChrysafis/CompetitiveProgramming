#include <iostream>
#include <bitset>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
using namespace std;
const int MOD = 1e9 + 7;
void solve(){
    int n;
    cin >> n;
    long long arr[n];
    long long cur = 0;
    for(int i = 0; i < n; i++){
        cin >> arr[i];
        cur ^= arr[i];
    }
    if(!cur){
        cout << "YES" << endl;
        return;
    }
    long long pref[n + 1];
    pref[0] = arr[0];
    for(int i = 1; i < n; i++){
        pref[i] = pref[i - 1] ^ arr[i];
    }
    long long suf[n + 1];
    suf[n - 1] = arr[n - 1];
    for(int i = n - 2; i >= 0; i--){
        suf[i] = suf[i + 1] ^ arr[i];
    }
    for(int i = 0; i < n; i++){
        for(int j = i + 1; j < n; j++){
            long long left = pref[i];
            long long right = suf[j];
            long long mid = cur ^ (pref[i] ^ suf[j]);
            if(left == right && right == mid && left == mid){
                cout << "YES" << endl;
                return;
            }
        }
    }
    cout << "NO" << endl;
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
