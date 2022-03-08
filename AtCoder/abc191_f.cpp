#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <cmath>
#include <map>
#include <random>
#include <ctime>
#include <cstdlib>
#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")

using namespace std;
int gcd (int u, int v) {
    if (!u || !v) {
        return max(u, v);
    }
    return gcd(max(u, v) % min(u, v), min(u, v));
}
set<int> modify (set<int> &s, int mn) {
    set<int> mySet = s;
    for (int i: s) {
        for (int j: s) {
            if (gcd(i, j) <= mn) {
                mySet.insert(gcd(i, j));
            }
        }
    }
    return mySet;
}
int main() {
    //freopen("input.txt", "r", stdin);
    srand(time(nullptr));
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N;
    cin >> N;
    vector<int> a(N);
    for (int i = 0; i < N; i++) {
        cin >> a[i];
    }
    sort(a.begin(), a.end());
    map<int,vector<int>> myMap;
    for (int i = 0; i < N; i++) {
        for (int j = 1; j <= sqrt(a[i]); j++) {
            if (a[i] % j ==  0) {
                if (j <= a[0]) myMap[j].push_back(i);
                if (a[i]/j <= a[0]) myMap[a[i]/j].push_back(i);
            }
        }
    }
    int cntr = 0;
    for (auto& p: myMap) {
        int g = 0;
        for (int x: p.second) {
            g = gcd(a[x], g);
        }
        //cout << g << " " << p.first << '\n';
        cntr += (g == p.first);
    }
    cout << cntr;
}
