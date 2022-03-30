#include <vector>
#include <algorithm>
#include <iostream>
#include <set>
#include <cmath>
#include <map>
#include <random>
#include <cassert>
#include <ctime>
#include <cstdlib>
#include <queue>
#include <limits.h>
 
using namespace std;
int64_t find_sum (vector<int64_t>& pref, int l, int r) {
    return pref[r + 1] - pref[l];
}
int64_t x;
bool canDo (vector<int64_t> &pref, vector<int64_t> &arr, int64_t k) {
    for (int i = 0; i < arr.size(); i++) {
        if (arr[i] > k) {
            return false;
        }
    }
    vector<pair<int,int>> vec;
    vec.push_back({0, 0});
    for (int i = 1; i < arr.size(); i++) {
        if (find_sum(pref, vec.back().first, i) > k) {
            vec.push_back({i, i});
        } else {
            vec.back().second++;
        }
    }
    return (vec.size() <= x);
}
int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int64_t n;
    cin >> n >> x;
    vector<int64_t> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    vector<int64_t> pref = {0};
    for (int i = 0; i < n; i++) {
        pref.push_back(pref.back() + arr[i]);
    }
    int64_t l = 0;
    int64_t r = 1e18;
    while (l != r) {
        int64_t m = (l + r )/2;
        if (canDo(pref, arr, m)) {
            r = m;
        } else {
            l = m + 1;
        }
    }
    cout << l << '\n';
}
