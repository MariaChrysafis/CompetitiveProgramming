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
    map<long long, long long> oc;
    for(int i = 0; i < n; i++){
        cin >> arr[i];
        oc[arr[i]]++;
    }
    long long ans = 0;
    for(pair<long long, long long> p: oc){
        ans += min(p.second, p.first - 1);
    }
    cout << ans << endl;
}
int main(){
    int t;
    cin >> t;
    while(t--){
        solve();
    }
}
