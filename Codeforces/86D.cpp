#include <iostream>
#include <vector>
#include <chrono>
#include <cstdint>
#include <algorithm>
#include <set>
#include <cmath>
#include <queue>
#include <deque>
#include <cassert>
#include <map>
#include <iomanip>
#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")

using namespace std;
typedef long long ll;
vector<ll> oc(1000000);
ll ans = 0;
void add (int val) {
    ans -= oc[val] * oc[val] * val;
    oc[val]++;
    ans += oc[val] * oc[val] * val;
}
void remove (int val) {
    ans -= oc[val] * oc[val] * val;
    oc[val]--;
    ans += oc[val] * oc[val] * val;
}
vector<int> a;
int sz;
bool comp (pair<pair<int,int>,int> p1, pair<pair<int,int>,int> p2) {
    return make_pair(p1.first.first/sz, p1.first.second) < make_pair(p2.first.first/sz, p2.first.second);
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N;
    cin >> N;
    sz = sqrt(N);
    int Q;
    cin >> Q;
    a.resize(N);
    for (int i = 0; i < N; i++) {
        cin >> a[i];
    }
    vector<pair<pair<int,int>,int>> vec(Q);
    for (int i = 0; i < Q; i++) {
        int l, r;
        cin >> l >> r;
        l-- , r--;
        vec[i] = {{l, r}, i};
    }
    sort(vec.begin(), vec.end(), comp);
    ll res[Q];
    int prevL = 0;
    int prevR = -1;
    for (int i = 0; i < vec.size(); i++) {
        pair<int,int> p = vec[i].first;
        while (prevR < p.second) {
            add(a[++prevR]);
        }
        while (prevR > p.second) {
            remove(a[prevR--]);
        }
        while (prevL < p.first) {
            remove(a[prevL++]);
        }
        while (prevL > p.first) {
            add(a[--prevL]);
        }
        res[vec[i].second] = ans;
    }
    for (ll i: res) {
        cout << i << '\n';
    }

}
