#include <cmath>
#include <iostream>
#include <set>
#include <climits>
#include <algorithm>
#include <cassert>
#include <vector>
#include <iomanip>
#include <type_traits>
#include <string>
#include <queue>
#include <map>
using namespace std;
#define ll long long
const int MAX = 1e4 + 5;
vector<int> primes;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    vector<bool> isPrime(350);
    for (int i = 0; i < isPrime.size(); i++) {
        isPrime[i] = true;
    }
    isPrime[0] = isPrime[1] = false;
    for (int i = 2; i < isPrime.size(); i++) {
        if (isPrime[i]) {
            primes.push_back(i);
            for (int j = 2 * i; j < isPrime.size(); j += i) {
                isPrime[j] = false;
            }
        }
    }
    vector<vector<double>> dp(primes.size() + 1);
    for (int i = 0; i < dp.size(); i++) {
        dp[i].resize(MAX);
        for (int j = 0; j < dp[i].size(); j++) {
            dp[i][j] = -10000;
        }
        dp[i][0] = 0;
    }
    vector<vector<int>> prev(dp.size());
    for (int i = 0; i < dp.size(); i++) {
        prev[i].resize(MAX);
    }
    for (int i = 1; i < dp.size(); i++) {
        for (int j = 1; j < dp[i].size(); j++) {
            dp[i][j] = dp[i - 1][j];
            prev[i][j] = prev[i - 1][j];
            if (dp[i][j - 1] > dp[i][j]) {
                prev[i][j] = prev[i][j - 1];
                dp[i][j] = dp[i][j - 1];
            }
            ll powr = primes[i - 1];
            while (j >= powr) {
                if (dp[i][j] < dp[i - 1][j - powr] + log2(powr)) {
                    dp[i][j] = dp[i - 1][j - powr] + log2(powr);
                    prev[i][j] = powr;
                }
                powr *= primes[i - 1];
            }
        }
    }
    map<int,int> myMap;
    for (int i = 0; i < primes.size(); i++) {
        long long powr = primes[i];
        while (powr < (int)1e4) {
            myMap[powr] = i;
            powr *= primes[i];
        }
    }
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        int cur = n;
        vector<int> a;
        int sz = dp.size() - 1;
        while (cur != 0 && sz > 0) {
            int val = prev[sz][cur];
            sz = myMap[val];
            cur -= val;
            a.push_back(val);
        }
        int ans = n;
        for (int i: a) {
            ans -= i;
        }
        while(ans != 0) {
            a.push_back(1);
            ans--;
        }
        sort(a.begin(), a.end());
        vector<vector<int>> v;
        int cntr = 1;
        for (int i = 0; i < a.size(); i++) {
            v.emplace_back();
            for (int j = 0; j < a[i]; j++) {
                v.back().push_back(cntr);
                cntr++;
            }
        }
        for (int i = 0; i < v.size(); i++) {
            for (int j = 0; j < v[i].size(); j++) {
                cout << v[i][(j + 1) % v[i].size()] << " ";
            }
        }
        cout << endl;
    }
}
