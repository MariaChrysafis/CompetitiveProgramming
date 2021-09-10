#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
 
using namespace std;
long long p;
long long pow4(long long x){
    x %= p;
    x *= x;
    x %= p;
    x *= x;
    return (x % p);
}
 
int main() {
    long long n, k;
    cin >> n >> p >> k;
    k % p;
    vector<long long> arr(n);
    map<long long, int> oc;
    for(int i = 0; i < n; i++) {
        cin >> arr[i];
        oc[(pow4(arr[i]) + (k * (p - arr[i])) % p) % p]++;
    }
    long long ans = 0;
    for(pair<long long,int> p: oc){
        ans += p.second * (p.second - 1)/2;
    }
    cout << ans << endl;
}
