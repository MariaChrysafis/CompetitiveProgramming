#include <cmath>
#include <cassert>
#include <iostream>
#include <set>
#include <climits>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <type_traits>
#include <string>
#include <queue>
#include <map>
#include <stack>

#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")
#pragma GCC optimization ("Ofast")
using namespace std;

int64_t dist (pair<int64_t, int64_t> p, pair<int64_t, int64_t> q) {
    return abs(p.first - q.first) * abs(p.first - q.first) + abs(p.second - q.second) * abs(p.second - q.second);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N, Q;
    cin >> N >> Q;
    vector<pair<int64_t,int64_t>> vec(N);
    for (int i = 0; i < N; i++) {
        cin >> vec[i].first >> vec[i].second;
    }
    while (Q--) {
        int64_t w, x, y;
        cin >> w >> x >> y;
        vector<int64_t> v1, v2;
        for (int i = 0; i < N; i++) {
            if (i == w) {
                continue;
            }
            v1.push_back(dist(vec[i], vec[w]));
            v2.push_back(dist(vec[i], {x,y}));
        }
        sort(v1.begin(), v1.end());
        sort(v2.begin(), v2.end());
        vec[w] = {x, y};
        if (v1 == v2) {
            cout << "equal\n";
            continue;
        }
        for (int i = 0; i < v1.size(); i++) {
            if (v1[i] > v2[i]) {
                cout << "smaller\n";
                break;
            } else if (v1[i] < v2[i]) {
                cout << "larger\n";
                break;
            }
        }
    }

}
