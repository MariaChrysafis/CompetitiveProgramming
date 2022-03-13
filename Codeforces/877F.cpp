#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <cmath>
#include <cassert>
#include <map>
#include <random>
#include <ctime>
#include <cstdlib>

using namespace std;

vector<int64_t> pref;
vector<int64_t> myMap(3e5 + 3);
map<int64_t,int64_t> id;
int64_t get_id1[(int64_t)1e5 + 1];
int64_t get_id2[(int64_t)1e5 + 1];
int64_t get_id3[(int64_t)1e5 + 1];
int64_t ans = 0;
int64_t K;

void add_left (int64_t x) {
    ans += myMap[get_id3[x + 1]];
    myMap[get_id1[x + 1]]++;
}

void add_right (int64_t x) {
    ans += myMap[get_id2[x + 1]];
    myMap[get_id1[x + 1]]++;
}

void remove_left (int64_t x) {
    myMap[get_id1[x + 1]]--;
    ans -= myMap[get_id3[x + 1]];
}

void remove_right (int64_t x) {
    myMap[get_id1[x + 1]]--;
    ans -= myMap[get_id2[x + 1]];
}

bool comp (pair<pair<int64_t,int64_t>,int64_t> p3, pair<pair<int64_t,int64_t>,int64_t> p4) {
    return (pair<int64_t,int64_t>){p3.first.first/400, p3.first.second} < (pair<int64_t,int64_t>){p4.first.first/400, p4.first.second};
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int64_t N; cin >> N >> K;
    vector<int64_t> t(N), a(N);
    for (int64_t i = 0; i < N; i++) {
        cin >> t[i];
    }
    for (int64_t i = 0; i < N; i++) {
        cin >> a[i];
    }
    pref.resize(N + 1);
    pref[0] = 0;
    for (int64_t i = 1; i <= N; i++) {
        if (t[i - 1] == 1) {
            pref[i] = pref[i - 1] + a[i - 1];
        } else {
            pref[i] = pref[i - 1] - a[i - 1];
        }
    }
    set<int64_t> s;
    for (int64_t i: pref) {
        s.insert(i), s.insert(i - K), s.insert(i + K);
    }
    int64_t cntr = 0;
    for (int64_t i: s) {
        id[i] = cntr++;
    }
    int64_t Q;
    cin >> Q;
    vector<pair<pair<int64_t,int64_t>,int64_t>> vec(Q);
    for (int64_t i = 0; i < Q; i++) {
        int64_t l, r;
        cin >> l >> r;
        l--, r--;
        vec[i] = {{l, r}, i};
    }
    sort(vec.begin(), vec.end(), comp);
    for (int64_t i = 0; i < pref.size(); i++) {
        get_id1[i] = id[pref[i]];
        get_id2[i] = id[pref[i] - K];
        get_id3[i] = id[pref[i] + K];
    }
    int64_t q[Q];
    int64_t tl = 0;
    int64_t tr = -1;
    for (auto& p: vec) {
        while (tl > p.first.first) {
            add_left(--tl);
        }
        while (tl < p.first.first) {
            remove_left(tl++);
        }
        while (tr > p.first.second) {
            remove_right(tr--);
        }
        while (tr < p.first.second) {
            add_right(++tr);
        }
        q[p.second] = ans + myMap[get_id3[tl]];
    }
    for (int64_t i: q) {
        cout << i << '\n';
    }
}
