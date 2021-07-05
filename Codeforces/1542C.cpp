#include <iostream>
#include <vector>
using namespace std;
const int MPRIME = 43;
vector<long long> primes = {2,3,5,7,11,13,17,19,23,29,31,37,41,43};
vector<long long> prefix;
const long long MOD = 1e9 + 7;
const long long MAX = 1e16 + 7;
long long solve(long long a, long long cur){
    long long invalid = cur/prefix[a];
    long long tot =  cur/prefix[a - 1];
    return tot - invalid;
}
pair<long long,long long> base(long long x){
    for(int p: primes){
        long long cntr = 1;
        for(int j = 0; j < 100; j++){
            if(cntr > MAX){
                continue;
            }
            cntr *= p;
            if(cntr == x){
                return {p, j + 1};
            }
        }
    }
    return {0, 0};
}
long long solve(long long y){
    long long ans = 0;
    for(int i = 1; i < MPRIME + 1; i++){
        pair<long long,long long> p = base(i);
        if(p.first == 0) continue;
        long long x = solve(i, y);
        ans += (i * x) % MOD;
        ans %= MOD;
    }
    return ans;
}
int main(){
    int t;
    cin >> t;
    prefix.resize(MPRIME + 1);
    prefix[0] = prefix[1] = 1;
    int cur = 0;
    for(int i = 2; i < MPRIME + 1; i++) {
        prefix[i] = prefix[i - 1];
        if (primes[cur] == i) {
            prefix[i] *= i;
            cur++;
        }else{
            pair<int,int> p = base(i);
            if(p.first == 0) continue;
            prefix[i] *= p.first;
        }
    }
    while(t--){
        long long x;
        cin >> x;
        cout << solve(x) << endl;
    }
}
