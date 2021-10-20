#include <iostream>
#include <cmath>
#include <queue>
#include <vector>
#include <algorithm>
#include <cassert>
#define ll int

using namespace std;
int main() {
    long long n;
    cin >> n;
    vector<pair<long long, long long>> primes;
    long long SQ = sqrt(n);
    for (long long i = 2; i <= SQ; i++) {
        if (n % i == 0) {
            long long cntr = 0;
            while (n % i == 0) {
                n /= i;
                cntr++;
            }
            primes.emplace_back(i, cntr);
        }
    }
    if (n != 1) {
        primes.emplace_back(n, 1);
    }
    long long ans = 0;
    for (auto p: primes) {
        //cout << p.first << " " << p.second << endl;
        long long cntr = 0;
        while (cntr * (cntr + 1)/2 < p.second) {
            ans++, cntr++;
        }
        if (cntr * (cntr + 1)/2 != p.second) ans--;
    }
    cout << ans;
}
