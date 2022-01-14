#include <vector>
#include <chrono>
#include <iostream>
#include <map>
#include <set>
#include <climits>
#include <cmath>
#include <cassert>
#include <queue>
#include <algorithm>

#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")

using namespace std;

typedef long long ll;

const int MAX = 2097152 + 1;

vector<int> cnt1, cnt2;

struct Interval {
    int val; //the interval has val intervals wiht a bitwise XOR of k
};

vector<int> pref;

void addBegin (ll &x, int ind, int K) {
    cnt1[pref[ind + 1]]++;
    cnt2[pref[ind]]++;
    x += cnt1[K ^ pref[ind]];
    //cout << "AB" << ind << ":" << x << '\n';
}

void removeBegin (ll& x, int ind, int K) {
    x -= cnt1[K ^ pref[ind]];
    cnt1[pref[ind + 1]]--;
    cnt2[pref[ind]]--;
    //cout << "RB" << ind << ":" << x << '\n';
}

void addEnd (ll &x, int ind, int K) {
    cnt1[pref[ind + 1]]++;
    cnt2[pref[ind]]++;
    x += cnt2[K ^ pref[ind + 1]];
    //cout << "AE" << ind << ":" << x << '\n';
}

void removeEnd (ll& x, int ind, int K) {
    x -= cnt2[K ^ pref[ind + 1]];
    cnt1[pref[ind + 1]]--;
    cnt2[pref[ind]]--;
    //cout << "RE" << ind << ":" << x << '\n';
}

int sq;

bool comp (pair<pair<int,int>,int> p1, pair<pair<int,int>,int> p2) {
    pair<int,int> a = {p1.first.first/sq, p1.first.second};
    pair<int,int> b = {p2.first.first/sq, p2.first.second};
    return (a < b);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cnt1.resize(MAX), cnt2.resize(MAX);
    int N, Q, K;
    cin >> N >> Q >> K;
    sq = sqrt(N);
    int a[N];
    for (int i = 0; i < N; i++) {
        cin >> a[i];
    }
    pref.resize(N + 1);
    pref[0] = 0;
    for (int i = 1; i <= N; i++) {
        pref[i] = pref[i - 1] ^ a[i - 1];
    }
    int prevLeft = 0;
    int prevRight = -1;
    ll cur = 0;
    vector<pair<pair<int,int>,int>> vec;
    for (int i = 0; i < Q; i++) {
        int l, r;
        cin >> l >> r;
        l--, r--;
        vec.push_back({{l, r}, i});
    }
    sort(vec.begin(), vec.end(), comp);
    ll ans[Q];
    for (int i = 0; i < Q; i++) {
        int l = vec[i].first.first;
        int r = vec[i].first.second;
        while(l < prevLeft) {
            addBegin(cur, --prevLeft, K);
        }
        while(r > prevRight) {
            addEnd(cur, ++prevRight, K);
        }
        while(l > prevLeft) {
            removeBegin(cur, prevLeft++, K);
        }
        while(r < prevRight) {
            removeEnd(cur, prevRight--, K);
        }
        ans[vec[i].second] = cur;
    }
    for (ll i: ans) {
        cout << i << ' ';
    }
    cout << '\n';
}
