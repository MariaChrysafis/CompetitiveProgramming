/*
ID: maria.c2
TASK: hamming
LANG: C++14
*/
#include <iostream>
#include <vector>
#include <cassert>
#include <map>
#include <set>
#include <chrono>
#include <queue>
#include <algorithm>
#include <cmath>
#include <fstream>

#pragma GCC optimize("O2")
using namespace std;
int bitCount(int x){
    int ans = 0;
    for (int i = 0; i < 8; i++) {
        ans += (bool)(x & (1 << i));
    }
    return ans;
}
bool valid(vector<int> v, int d) {
    for (int i = 0; i < v.size() - 1; i++) {
        if (bitCount(v[i] ^ v.back()) < d) {
            return false;
        }
    }
    return true;
}
int main() {
    freopen("hamming.in", "r", stdin);
    freopen("hamming.out", "w", stdout);
    int n, b, d;
    cin >> n >> b >> d;
    vector<int> ans;
    for (int i = 0; i < 256; i++) {
        ans.push_back(i);
        if(!valid(ans, d)) {
            ans.pop_back();
        }
    }
    for (int i = 0; i < n - 1; i++) {
        cout << ans[i];
        if (i % 10 == 9) {
            cout << endl;
        } else {
            cout << " ";
        }
    }
    cout << ans[n - 1] << endl;
}
