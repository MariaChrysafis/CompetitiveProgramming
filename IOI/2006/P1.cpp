#include <cmath>
#include <cassert>
#include <iostream>
#include <set>
#include <climits>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <type_traits>
#include <string>
#include <queue>
#include <map>
#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("Ofast")
#pragma GCC optimization ("unroll-loops")

using namespace std;

class HashString {
    map<char,int> oc;
public:
    void add (char c) {
        oc[c]++;
    }
    void remove (char c) {
        oc[c]--;
        if (oc[c] == 0) {
            oc.erase(c);
        }
    }
    bool operator == (HashString &hs) const {
        return (hs.oc == oc);
    }
    void print () {
        for (auto& p: oc) {
            cout << p.first << " " << p.second << '\n';
        }
        cout << '\n';
    }
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int N, M;
    string s, t;
    cin >> N >> M >> s >> t;
    if (t.length() < s.length()) {
        cout << "0\n";
        return 0;
    }
    HashString hs1, hs2;
    for (char c: s) {
        hs1.add(c);
    }
    int cntr = 0;
    for (int i = 0; i < s.length(); i++) {
        hs2.add(t[i]);
    }
    cntr += (hs1 == hs2);
    for (int i = 0; i + s.length() < t.length(); i++) {
        hs2.remove(t[i]);
        hs2.add(t[i + s.length()]);
        cntr += (hs1 == hs2);
    }
    cout << cntr;
}
