#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <cmath>
#include <map>
#include <random>
#include <ctime>
#include <cstdlib>
#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")
 
using namespace std;
int main() {
    //freopen("inp.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    vector<int64_t> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vector<int64_t> mu;
    mu.assign(1e6 + 1, 0);
    for (int64_t i = 2; i < mu.size(); i++) {
        if (mu[i] == 0) {
            for (int j = i; j < mu.size(); j += i) {
                mu[j]++;
            }
        }
    }
    for (int64_t i = 2; i < mu.size(); i++) {
        for (int64_t j = i * i; j < mu.size(); j += i * i) {
            //cout << i << " " << j << '\n';
            mu[j] = 0;
        }
    }
    for (int i = 0; i < mu.size(); i++) {
        if (!mu[i]) {
            continue;
        }
        mu[i] %= 2;
        mu[i] = pow(-1, mu[i]);
    }
    mu[1] = 1;
    vector<int64_t> d;
    vector<int64_t> c(mu.size());
    for (int i: a) {
        c[i]++;
    }
    d.assign(mu.size(), 0);
    for (int i = 1; i < mu.size(); i++) {
        for (int j = i; j < mu.size(); j += i) {
            d[i] += c[j];
        }
    }
    int64_t ans = 0;
    for (int i = 1; i < d.size(); i++) {
        ans += mu[i] * d[i] * (d[i] - 1)/2;
    }
    cout << ans;
}
