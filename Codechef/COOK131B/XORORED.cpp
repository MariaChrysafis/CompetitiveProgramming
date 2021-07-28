#include <iostream>
#include <vector>
#include <map>
#include <cassert>
#include <set>
#include <unordered_set>
#include <algorithm>
#include <random>
#include <chrono>
#include <queue>
#include <array>

#define ll long long
#define endl '\n'

using namespace std;
long long gcd(long long a, long long b){
    if(min(a,b) == 0) return max(a,b);
    else return gcd(max(a,b) % min(a,b), min(a,b));
}
void solve(){
    int n;
    cin >> n;
    vector<long long> arr(n);
    for(int i = 0; i < n; i++){
        cin >> arr[i];
    }
    long long ans = 0;
    long long res = 0;
    for(int i = 0; i < 30; i++){
        long long cntr = 0;
        for(long long j: arr) {
            if ((j & (1 << i))) {
                cntr++;
            }
        }
        if(cntr == n){
            ans += (1 << i);
        }else if(cntr != 0){
            res += (1 << i);
        }
    }
    cout << ans << " " << res << endl;
}
int main(){
    int t;
    cin >> t;
    while(t--){
        solve();
    }
}
