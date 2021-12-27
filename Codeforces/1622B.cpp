#include <iostream>
#include <cmath>
#include <vector>
#include <set>
#include <chrono>
#include <random>
#include <queue>
#include <cstdint>
#include <cassert>
#include <bitset>
#include <map>
#include <list>
#include <stack>
#include <algorithm>

#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")
typedef long long ll;
using namespace std;

vector<int> comp (vector<int> v1, vector<int> v2) {
    vector<pair<int,int>> vec;
    for (int i = 0; i < v1.size(); i++) {
        vec.push_back({v1[i], i});
    }
    sort(vec.begin(), vec.end());
    for (int i = 0; i < vec.size(); i++) {
        v1[vec[i].second] = v2[i];
    }
    return v1;
}

void solve () {
    int n;
    cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }
    string s;
    cin >> s;
    vector<int> zero, one;
    for (int i = 0; i < n; i++) {
        if (s[i] == '1') one.push_back(v[i]);
        else zero.push_back(v[i]);
    }
    vector<int> des_zero, des_one;
    for (int i = 0; i < zero.size(); i++) {
        des_zero.push_back(i + 1);
    }
    for (int i = 0; i < one.size(); i++) {
        des_one.push_back(zero.size() + i + 1);
    }
    vector<int> z = comp(zero, des_zero);
    vector<int> o = comp(one, des_one);
    int o_c = 0;
    int z_c = 0;
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == '0') {
            cout << z[z_c++] << ' ';
        } else {
            cout << o[o_c++] << ' ';
        }
    }
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }

}
