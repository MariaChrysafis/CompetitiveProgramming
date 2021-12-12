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
int main() {
    freopen("recording.in", "r", stdin);
    freopen("recording.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    vector<pair<int,int>> vec(n);
    for (int i = 0; i < n; i++) {
        cin >> vec[i].first >> vec[i].second;
    }
    for (auto& p: vec) {
        swap(p.first, p.second);
    }
    sort(vec.begin(), vec.end());
    for (auto& p: vec) {
        swap(p.first, p.second);
    }
    int a = 0;
    int b = 0;
    int ans = 0;
    for (auto& p: vec) {
        if (p.first < a) {
            continue;
        }
        if (p.first < b) {
            a = b, b = p.second, ans++;
        } else {
            b = p.second, ans++;
        }
    }
    cout << ans;
}
