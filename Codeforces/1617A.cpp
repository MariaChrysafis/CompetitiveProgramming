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
#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
using namespace std;

int gcd(int a, int b) {
    if (!a || !b) return max(a, b);
    return gcd(max(a, b) % min(a, b), min(a, b));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    vector<string> pos = {"abc", "acb", "bac", "bca", "cab", "cba"};
    int dum;
    cin >> dum;
    while (dum--) {
        string s, t;
        cin >> s >> t;
        map<char,int> oc;
        for (char c: s) oc[c]++;
        vector<string> pot;
        for (auto& q: pos) {
            if (q == t) {
                continue;
            }
            pot.push_back("");
            for (int i = 0; i < q.length(); i++) {
                for (int j = 0; j < oc[q[i]]; j++) {
                    pot.back() += q[i];
                }
            }
            for (char c = 'd'; c <= 'z'; c++) {
                for (int j = 0; j < oc[c]; j++) {
                    pot.back() += c;
                }
            }
        }
        sort(pot.begin(), pot.end());
        cout << pot[0] << '\n';
    }
}
