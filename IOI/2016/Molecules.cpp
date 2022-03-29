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
#include <limits.h>
#include "molecules.h"
 
using namespace std;
 
int in_range(vector<int64_t> &pref, int64_t l, int64_t r) {
    if (pref.back() < l) {
        return -1;
    }
    int tl = 0;
    int tr = pref.size() - 1;
    while (tl != tr) {
        int tm = (tl + tr) / 2;
        if (pref[tm] >= l) {
            tr = tm;
        } else {
            tl = tm + 1;
        }
    }
    if (pref[tl] >= l && pref[tl] <= r) {
        return tl;
    }
    return -1;
}
 
vector<int> find_subset(int l, int r, vector<int> w) {
    for (int i = 0; i < w.size(); i++) {
        if (w[i] >= l && w[i] <= r) {
            return {i};
        }
    }
    vector<pair<int64_t, int>> vec;
    for (int i = 0; i < w.size(); i++) {
        vec.push_back({w[i], i});
    }
    sort(vec.begin(), vec.end());
    vector<int64_t> pref = {0};
    for (int i = 0; i < vec.size(); i++) {
        pref.push_back(pref.back() + vec[i].first);
    }
    for (int i = 0; i < pref.size(); i++) {
        if (in_range(pref, pref[i] + l, pref[i] + r) != -1) {
            int x = in_range(pref, pref[i] + l, pref[i] + r);
            vector<int> ans;
            for (int j = i; j <= x - 1; j++) {
                ans.push_back(vec[j].second);
            }
            return ans;
        }
    }
    return {};
}
 
void print(vector<int> v) {
    for (int i: v) {
        cout << i << ' ';
    }
    cout << '\n';
}
 
 
/*
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    print(find_subset(15, 17, {6, 8, 8, 7}));
}
 
 
 */
