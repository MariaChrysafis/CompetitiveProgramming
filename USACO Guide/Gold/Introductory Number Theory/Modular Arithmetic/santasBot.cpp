#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <unordered_map>
const unsigned long MOD = 998244353;
using namespace std;
unsigned long pwr(unsigned long long a, unsigned long b) {
    if(b == 0) return 1;
    if(b == 1) return a;
    unsigned long long res = 1;
    while (b != 0) {
        if (b & 1 == 1) res = (1LL * res * a) % MOD;
        a *= a;
        a %= MOD;
        b >>= 1;
    }
    return res;
}
unsigned long frac(unsigned long long a, unsigned long long b){
    return (a * pwr(b, MOD - 2)) % MOD;
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    unordered_map<int,vector<int>> childToPresent;
    unordered_map<int,int> presToOc;
    int n;
    cin >> n;
    for(int i = 0; i < n; i++){
        int k;
        cin >> k;
        childToPresent[i].resize(k);
        for(int j = 0; j < k; j++){
            cin >> childToPresent[i][j];
            presToOc[childToPresent[i][j]]++;
        }
    }
    unsigned long ans = 0;
    for(int x = 0; x < n; x++){
        for(int y: childToPresent[x]){
            //Then find probability
            int a1 = childToPresent[x].size(); /*number of presents child has*/
            int a2 = presToOc[y];
            pair<unsigned long,unsigned long> p = make_pair(a2,1);
            pair<unsigned long, unsigned long> r = make_pair(1,a1);
            pair<unsigned long, unsigned long> s = make_pair(1,n);
            unsigned long long l1 = frac(p.first,p.second);
            unsigned long l2 = frac(r.first,r.second);
            unsigned long l3 = frac(s.first,s.second);
            ans += (((l1 * l2) % MOD * l3) % MOD * l3) % MOD;
            ans %= MOD;
        }
    }
    cout << ans << endl;
}
