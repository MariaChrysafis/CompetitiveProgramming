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
#include <queue>
#include <algorithm>
#include <string>

using namespace std;

typedef long long ll;
static const int MAX = 1e6 + 1;
vector<int> mob;
vector<int> fact[MAX];
void sieve () {
    vector<ll> lpf;
    lpf.assign(MAX, 1e9);
    lpf[1] = 1;
    for (int i = 2; i < lpf.size(); i++) {
        if (lpf[i] == 1e9) {
            lpf[i] = i;
            for (int j = 2 * i; j < lpf.size(); j += i) {
                if (lpf[j] == 1e9) {
                    lpf[j] = i;
                }
            }
        }
    }
    mob.assign(MAX, -2);
    for (int i = 2; i < MAX; i++) {
        if (i/lpf[i] == lpf[i] || !mob[i/lpf[i]]) {
            mob[i] = 0;
            continue;
        }
    }
    for (int i = 2; i <= sqrt(MAX); i++) {
        for (int j = i * i; j < MAX; j += i * i) {
            mob[j] = 0;
        }
    }
    for (int i = 1; i < MAX; i++) {
        if (mob[i] == 0) continue;
        for (int j = i; j < MAX; j += i) {
            fact[j].push_back(i);
        }
    }
    mob[1] = 1;
    for (int i = 2; i < MAX; i++) {
        if (mob[i] == 0) {
            continue;
        }
        mob[i] = -mob[i/lpf[i]];
    }
}
struct Cumulative_GCD_Pairs {
    vector<ll> oc; //how many things are divisible by x
    vector<ll> g; //how many pairs are there such that both are divisible by g

    ll get (ll x) {
        ll ans = 0;
        for (int i = x; i < oc.size(); i += x) {
            ans += mob[i/x] * g[i];
        }
        return ans;
    }

    void add (ll x) {
        for (ll i: fact[x]) {
            g[i] -= oc[i] * (oc[i] - 1) * (oc[i] - 2)/6;
            oc[i]++;
            g[i] += oc[i] * (oc[i] - 1) * (oc[i] - 2)/6;
        }
    }

    void resz () {
        g.assign(MAX, 0);
        oc.assign(MAX, 0);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    sieve();
    Cumulative_GCD_Pairs gcdPairs;
    gcdPairs.resz();
    ll n;
    cin >> n;
    int arr[n];
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    for (int i = n - 1; i >= 0; i--) {
        gcdPairs.add(arr[i]);
    }
    cout << gcdPairs.get(1) << '\n';
}
