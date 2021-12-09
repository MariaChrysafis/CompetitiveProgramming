#include <algorithm>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <random>
#include <set>
#include <stack>
#include <vector>
#define ll long long
using namespace std;
const int MAX = 1e7 + 1;
int prime[MAX];
void fill () {
    for (int i = 0; i < MAX; i++) {
        prime[i] = 0;
    }
    prime[0] = prime[1] = 1;
    for (int i = 2; i < MAX; i++) {
        if (prime[i]) continue;
        prime[i] = i;
        for (int j = 2 * i; j < MAX; j += i) {
            if (!prime[j]) {
                prime[j] = i;
            }
        }
    }
}
vector<int> pos;
void generate (vector<pair<int,int>>& ref, int cur, int ind) {
    if (ind == ref.size()) {
        pos.push_back(cur);
        return;
    }
    for (int i = 0; i <= ref[ind].second; i++) {
        generate(ref, cur * pow(ref[ind].first,i), ind + 1);
    }
}
vector<int> factors (int n) {
    vector<pair<int,int>> vec;
    int dum = n;
    while (true) {
        if (prime[dum] == 1) {
            break;
        }
        int p = prime[dum];
        int cntr = 0;
        while (dum % p == 0) {
            cntr++;
            dum /= p;
        }
        vec.push_back({p, cntr});
    }
    pos.clear();
    generate(vec, 1, 0);
    return pos;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    fill();
    ll n;
    cin >> n;
    vector<pair<ll,ll>> v(n);
    vector<int> oc;
    oc.assign(MAX, 0);
    for (int i = 0; i < n; i++) {
        cin >> v[i].first;
        v[i].second = i;
    }
    sort(v.begin(), v.end());
    ll myMin = 1e15;
    pair<int, int> p;
    n = v.size();
    vector<pair<ll,ll>> fact[MAX];
    for (int i = 0; i < n; i++) {
        if (oc[v[i].first] >= 2) {
            continue;
        }
        oc[v[i].first]++;
        vector<int> f = factors(v[i].first);
        for (int j: f) {
            if (fact[j].size() <= 1) {
                fact[j].push_back(v[i]);
            }
        }
    }
    for (ll i = 1; i < MAX; i++) {
        if (fact[i].size() <= 1) {
            continue;
        }
        if (fact[i][0].first * fact[i][1].first / i < myMin) {
            myMin = fact[i][0].first * fact[i][1].first / i;
            p = {fact[i][0].second + 1, fact[i][1].second + 1};
        }
    }
    if (p.second < p.first) {
        swap(p.second, p.first);
    }
    cout << p.first << " " << p.second << '\n';
}
