#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
using namespace std;
long long MOD = 1e9 + 7;
vector<long long> fact;
long long mult(long long x, long long y){
    return (x * y) % MOD;
}
long long binPow(long long x, long long y){
    long long res = x;
    long long ans = 1;
    while(y > 0){
        if(y & 1){
            ans = mult(ans, res);
        }
        res = mult(res, res);
        y /= 2;
    }
    return ans;
}
long long inv(long long x){
    return binPow(x, MOD - 2);
}
long long combo(long long n, long long m){
    return mult(fact[n], inv(mult(fact[n - m], fact[m])));
}
void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> arr(n);
    map<int,int> oc;
    for(int i = 0; i < n; i++){
        cin >> arr[i];
        oc[arr[i]]++;
    }
    sort(arr.begin(), arr.end());
    reverse(arr.begin(), arr.end());
    map<int,int> ocDes;
    for(int i = 0; i < k; i++){
        ocDes[arr[i]]++;
    }
    long long ans = 1;
    for(pair<int,int> p: ocDes){
        long long x = oc[p.first];
        long long y = p.second;
        ans = mult(ans, combo(x, y));
    }
    cout << ans << endl;
}
int main(){
    fact.push_back(1);
    for(int i = 1; i <= 1000; i++){
        fact.push_back(mult(fact.back(), i));
    }
    int t;
    cin >> t;
    while(t--){
        solve();
    }
}
