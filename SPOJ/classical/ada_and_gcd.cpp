#include <vector>
#include <chrono>
#include <iostream>
#include <map>
#include <set>
#include <climits>
#include <cmath>
#include <cassert>
#include <iomanip>
#include <stack>
#include <unordered_map>
#include <queue>
#include <algorithm>
#include <string>

using namespace std;

typedef long long ll;
static const int MAX = 1e7 + 1;

const int MOD = 1e9 + 7;
bool comp (vector<int> &v1, vector<int> &v2) {
    if (v1.size() != v2.size()) return (v1.size() < v2.size());
    return (v1 < v2);
}

vector<int> compress (vector<int> v) {
    sort(v.begin(), v.end());
    vector<int> ans;
    for (int i = 0; i < v.size(); i++) {
        if (ans.empty() || v[i] != ans.back()) {
            ans.push_back(v[i]);
        }
    }
    return ans;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    vector<bool> isPrime;
    vector<int> index_to_prime;
    vector<int> prime_to_index(MAX), lpf(MAX);
    isPrime.assign(MAX, true);
    isPrime[0] = isPrime[1] = false;
    for (int i = 2; i < MAX; i++) {
        if (isPrime[i]) {
            lpf[i] = i;
            prime_to_index[i] = index_to_prime.size();
            index_to_prime.push_back(i);
            for (int j = 2 * i; j < MAX; j += i) {
                if (isPrime[j]) {
                    lpf[j] = i;
                }
                isPrime[j] = false;
            }
        }
    }
    int T;
    cin >> T;
    vector<vector<int>> vec(T);
    for (int i = 0; i < T; i++) {
        int N;
        cin >> N;
        vec[i].resize(N);
        for (int j = 0; j < N; j++) {
            cin >> vec[i][j];
        }
        if (i == 0 || N < vec[0].size()) {
            swap(vec[i], vec[0]);
        }
    }
    vector<int> min_oc;
    min_oc.assign(index_to_prime.size(), 1e9);
    for (int tc = 0; tc < T; tc++) {
        vector<int> oc(min_oc.size());
        for (int val: vec[tc]) {
            while (val != 1) {
                if (prime_to_index[lpf[val]] < oc.size()) oc[prime_to_index[lpf[val]]]++;
                val /= lpf[val];
            }
        }
        for (int i = 0; i < oc.size(); i++) {
            min_oc[i] = min(min_oc[i], oc[i]);
        }
        while (min_oc.back() == 0 && !min_oc.empty()) {
            min_oc.pop_back();
        }
    }
    ll ans = 1;
    for (int i = 0; i < index_to_prime.size(); i++) {
        while (min_oc[i]--) {
            ans *= index_to_prime[i], ans %= MOD;
        }
    }
    cout << ans;


}
