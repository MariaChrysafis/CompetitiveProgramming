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
#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")

typedef long long ll;

using namespace std;
ll f (ll l, ll r) {
    if (l == 0) {
        return max(r - 1, 0ll);
    }
    if (r == 0) {
        return max(l - 1, 0ll);
    }
    return (l + 1) * (r + 1) - 3;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string s;
    cin >> s;
    vector<pair<int,int>> vec;
    vec.push_back({0, -1});
    char prev = s[0];
    for (int i = 0; i < s.length(); i++) {
        if (prev == s[i]) {
            vec.back().second++;
        } else {
            vec.emplace_back(i, i);
            prev = s[i];
        }
    }
    ll answer = 0;
    for (int i = 0; i < vec.size(); i++) {
        if (vec[i].second - vec[i].first == 0) {
            int left = 0;
            int right = 0;
            if (i != 0) {
                left = vec[i - 1].second - vec[i - 1].first + 1;
            }
            if (i != vec.size() - 1) {
                right = vec[i + 1].second - vec[i + 1].first + 1;
            }
            answer += f(left, right);
        } else {
            if (i != 0) {
                answer += f(vec[i - 1].second - vec[i - 1].first + 1, 0);
            }
            if (i != vec.size() - 1) {
                answer += f(vec[i + 1].second - vec[i + 1].first + 1, 0);
            }
        }
    }
    cout << answer << '\n';
}
