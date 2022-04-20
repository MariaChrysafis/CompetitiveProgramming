#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <cassert>
#include <map>
#include <complex>
#include <cmath>
#include <stdio.h>
#include <string.h>
#include <set>
#include <queue>
#include"interactive.h"
using namespace std;
int beginning;
vector<int> permutation (vector<int> indices, int n) {
    vector<int> v1 = get_pairwise_xor(indices);
    indices.push_back(n);
    vector<int> v2 = get_pairwise_xor(indices);
    map<int,int> cnt;
    for (int i: v2) cnt[i]++;
    for (int i: v1) cnt[i]--;
    vector<int> v;
    for (auto& p: cnt) {
        if (p.second && p.first != 0)
            v.push_back(p.first ^ beginning);
    }
    return v;
}
vector<int> guess (int n) {
    beginning = ask(n);
    map<int,int> m;
    for (int i = 0; i < 7; i++) {
        vector<int> x;
        for (int j = 0; j < n - 1; j++) {
            if ((j + 1) & (1 << i)) {
                x.push_back(j + 1);
            }
        }
        if (x.empty()) {
            continue;
        }
        vector<int> a = permutation(x, n);
        for (int val: a) {
            m[val] |= (1 << i);
        }
    }
    vector<int> ans(n);
    for (auto& p: m) {
        ans[p.second - 1] = p.first;
    }
    ans.back() = beginning;
    return ans;
}
