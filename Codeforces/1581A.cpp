#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <algorithm>
#include <cmath>
#include <fstream>

using namespace std;
void print(vector<int> v) {
    for(int i: v) cout << i << " ";
    cout << endl;
}

bool valid(vector<int> v) {
    int cntr = 0;
    for(int i = 0; i < v.size() - 1; i++) {
        if(v[i] < v[i + 1]) {
            cntr++;
        }
    }
    return (cntr >= v.size()/2);
}

const int MOD = 1e9 + 7;

long long binPow(long long a, long long b) {
    long long ans = 1;
    long long res = a;
    while(b > 0) {
        if(b & 1) {
            ans *= res;
            ans %= MOD;
        }
        res *= res;
        res %= MOD;
        b >>= 1;
    }
    return ans;
}

long long inv(long long x) {
    return binPow(x, MOD - 2);
}

long long fact(long long x) {
    long long ans = 1;
    for(int i = 1; i <= x; i++) {
        ans *= i;
        ans %= MOD;
    }
    return ans;
}

void solve() {
    long long n;
    cin >> n;
    cout << (fact(2 * n) * inv(2)) % MOD << endl;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while(t--) {
        solve();
    }
}
