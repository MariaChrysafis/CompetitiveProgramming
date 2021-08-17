#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include <map>
 
#define ll long long
using namespace std;
 
struct BIT{
    vector<long long> bit; //1-indexed
    long long pref(long long ind){
        long long ans = 0;
        ind++;
        while(ind > 0){
            //cout << ind << " ";
            ans += bit[ind];
            ind -= (ind & (-ind));
        }
        return ans;
    }
    long long sum(long long l, long long r){
        if(l == 0){
            return pref(r);
        }
        return pref(r) - pref(l - 1);
    }
    void update(long long ind, long long val){
        ind++;
        while(ind < bit.size()){
            bit[ind] += val;
            ind += ind & (-ind);
        }
    }
    void construct(vector<long long> v){
        bit.resize(v.size() + 1);
        for(int i = 0; i <= v.size(); i++){
            bit[i] = 0;
        }
        for(int i = 0; i < v.size(); i++) {
            update(i, v[i]);
        }
    }
};
 
int mobius(int n) {
    if (n == 1) {
        return 1;
    }
    int p = 0;
    int orig = n;
    for (int i = 2; i <= sqrt(orig); i++) {
        if (n % i == 0) {
            n = n / i;
            p++;
            if (n % i == 0) {
                return 0;
            }
        }
    }
    if (n != 1) {
        p++;
    }
    if (p % 2 == 0) return 1;
    return -1;
}
 
const int MOD = 998244353;
 
ll solve(vector<ll> l, vector<ll> r, int m, int n) {
    for (int i = 0; i < n; i++) {
        r[i] -= l[i];
        m -= l[i];
    }
    if (m < 0) {
        return 0;
    }
    vector<ll> prev(m + 1);
    for (int i = 0; i <= m; i++) {
        prev[i] = 0;
    }
    for (int i = 0; i <= m; i++) {
        if (i <= r[0]) {
            prev[i] = 1;
        }
    }
    vector<ll> cur(m + 1);
    for (int i = 1; i < n; i++) {
        BIT b;
        b.construct(prev);
        for (int j = 0; j <= m; j++) {
            cur[j] = b.sum(j - min((int)r[i], j), j);
            cur[j] %= MOD;
        }
        swap(prev, cur);
    }
    ll ans = 0;
    for (int i = 0; i <= m; i++) {
        ans += prev[i];
        if (ans > MOD) ans -= MOD;
    }
    return ans;
}
 
int ceil(int a, int b) {
    return (a + (b - 1)) / b;
}
 
 
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m;
    cin >> n >> m;
    vector<ll> l(n), r(n);
    for (int i = 0; i < n; i++) {
        cin >> l[i] >> r[i];
    }
    ll ans = 0;
    for (int d = 1; d <= m; d++) {
        if (mobius(d) == 0) {
            continue;
        }
        vector<ll> left = l;
        vector<ll> right = r;
        for (int i = 0; i < left.size(); i++) {
            left[i] = ceil(left[i], d);
            right[i] = right[i] / d;
        }
        ans += mobius(d) * solve(left, right, m / d, n);
        if (ans < 0) ans += MOD;
        ans %= MOD;
    }
    cout << ans << endl;
}
