#include <iostream>
#include <cmath>
#include <vector>
#include <set>
#include <chrono>
#include <random>
#include <queue>
#include <cassert>
#include <map>
#include <algorithm>

#define ll long long
using namespace std;
map<int,int> oc;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    vector<bool> isPrime((int)2e6);
    isPrime.assign(isPrime.size(), true);
    isPrime[0] = isPrime[1] = false;
    for (int i = 2; i < isPrime.size(); i++) {
        if (isPrime[i]) {
            for (int j = 2 * i; j < isPrime.size(); j += i) {
                isPrime[j] = false;
            }
        }
    }
    vector<ll> primes;
    for (int i = 0; i < isPrime.size(); i++) {
        if (isPrime[i]) {
            primes.push_back(i);
        }
    }
    ll n, x, y;
    cin >> n >> x >> y;
    vector<ll> a(n);
    vector<ll> val(isPrime.size()), sum(isPrime.size());
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i: a) {
        val[i]++, sum[i] += i;
    }
    for (int i: primes) {
        for (int j = i; j < val.size(); j += i) {
            oc[i] += val[j];
        }
    }
    vector<ll> prefSum(val.size()), prefVal(val.size());
    prefSum[0] = 0, prefVal[0] = 0;
    for (int i = 1; i < prefSum.size(); i++) {
        prefSum[i] = prefSum[i - 1] + sum[i];
        prefVal[i] = prefVal[i - 1] + val[i];
    }
    ll myMin = LLONG_MAX;
    for (int p: primes) {
        ll ans = 0;
        int lambda = x/y;
        //ans % p is in the range [p - lambda, p - 1]
        lambda = min(lambda, p - 1);
        for (int i = 0; i + p < val.size(); i += p) {
            //[i + p - lambda, i + p - 1] -> add y
            //[i + 1, i + p - lambda - 1] -> add x
            ans += x * (prefVal[i + p - lambda - 1] - prefVal[i]);
            ans += y * ((i + p) * (prefVal[i + p - 1] - prefVal[i + p - lambda - 1]) - (prefSum[i + p - 1] - prefSum[i + p - lambda - 1]));
        }
        myMin = min(myMin, ans);
    }
    cout << myMin << endl;
}
