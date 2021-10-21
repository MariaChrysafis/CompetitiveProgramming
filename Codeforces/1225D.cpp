#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <map>
#include <queue>
#include <vector>

#define ll int

using namespace std;

const int MOD = (int)1e9 + 7;

long long binPow(long long x, long long y) {
    long long ans = 1;
    long long res = x;
    while (y > 0) {
        if (y & 1) {
            ans *= res;
            ans %= MOD;
        }
        res *= res;
        res %= MOD;
        y >>= 1;
    }
    return ans;
}

vector<pair<long long, long long>> factors(long long n) {
    vector<pair<long long, long long>> vec;
    const long long SQ = sqrt(n);
    for (long long i = 2; i <= SQ; i++) {
        if (n % i == 0) {
            long long cntr = 0;
            while (n % i == 0) {
                cntr++;
                n /= i;
            }
            vec.emplace_back(i, cntr);
        }
    }
    if (n != 1) {
        vec.emplace_back(n, 1);
    }
    return vec;
}

map<long long, long long> ind;

long long convert(int val, int k) {
    auto vec = factors(val);
    long long ans = 0;
    for (int i = 0; i < vec.size(); i++) {
        vec[i].second %= k;
        ans += vec[i].second * binPow(k, ind[vec[i].first]);
        ans %= MOD;
    }
    return ans;
}

long long convert_complement(long long val, long long k) {
    auto vec = factors(val);
    long long ans = 0;
    for (int i = 0; i < vec.size(); i++) {
        vec[i].second %= k;
        vec[i].second = (k - vec[i].second) % k;
        ans += vec[i].second * binPow(k, ind[vec[i].first]);
        ans %= MOD;
    }
    return ans;
}

int main() {
    int n, k;
    cin >> n >> k;
    if (k >= 33) {
        long long cntr = 0;
        for (int i = 0; i < n; i++) {
            int x;
            cin >> x;
            if (x == 1) {
                cntr++;
            }
        }
        cout << cntr * (cntr - 1)/2;
        return 0;
    }
    vector<bool> isPrime((int) 1e5 + 1);
    for (int i = 0; i < isPrime.size(); i++) {
        isPrime[i] = true;
    }
    isPrime[2] = true;
    vector<int> primes;
    for (int i = 2; i < (int) 1e5 + 1; i++) {
        if (isPrime[i]) {
            for (int j = 2 * i; j < (int) 1e5 + 1; j += i) {
                isPrime[j] = false;
            }
            primes.push_back(i);
        }
    }
    for (int i = 0; i < primes.size(); i++) {
        ind[primes[i]] = i;
    }
    map<int, int> oc;
    vector<int> v;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        oc[convert(x, k)]++;
        v.push_back(x);
    }
    long long ans = 0;
    for (int i = 0; i < n; i++) {
        bool b = convert_complement(v[i], k) == convert(v[i], k);
        ans += oc[convert_complement(v[i], k)] - b;
    }
    cout << ans / 2 << endl;
}
