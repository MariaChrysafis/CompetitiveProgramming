#include <iostream>
#include <vector>
#include <chrono>
#include <cstdint>
#include <algorithm>
#include <string>
#include <set>
#include <cmath>
#include <queue>
#include <deque>
#include <cassert>
#include <fstream>
#include <map>
#include <iomanip>
#include <sstream>
#pragma GCC optimization ("O1")
#pragma GCC optimization ("avx")
#pragma GCC optimize("unroll-loops")

using namespace std;
typedef long double ll;

void no () {
    cout << "No\n";
    exit(0);
}

void yes () {
    cout << "Yes\n";
    exit(0);
}

void print (vector<int> v) {
    for (int i: v) {
        cout << i << ' ';
    }
    cout << '\n';
}

map<vector<int>, bool> hv;

void rec (vector<int> v) {
    if (hv[v]) return;
    hv[v] = true;
    print(v);
    for (int i = 1; i < v.size() - 1; i++) {
        int prev = v[i];
        v[i] = v[i + 1] + v[i - 1] - v[i];
        rec(v);
        v[i] = prev;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }
    if (a[0] != b[0] || a.back() != b.back()) {
        no();
    }
    map<int,int> difA, difB;
    for (int i = 1; i < n; i++) {
        difA[abs(a[i] - a[i - 1])]++;
        difB[abs(b[i] - b[i - 1])]++;
    }
    for (auto& p: difA) {
        if (p.second != difB[p.first]) {
            no();
        }
    }
    //rec(a);
    yes();
}
