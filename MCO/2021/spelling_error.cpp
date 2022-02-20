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
#include <stack>

#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")
#pragma GCC optimization ("Ofast")
using namespace std;
vector<int64_t> powers1, powers2, powers3;
const int MOD1 = 1e9 + 7;
const int MOD2 = 1e9 + 9;
const int MOD3 = 998244353;
int64_t base = 53;

struct Triple {
    int64_t a, b, c;
    bool operator < (const Triple& t1) const {
        if (this->a != t1.a) {
            return (this->a < t1.a);
        }
        if (this->b != t1.b) {
            return (this->b < t1.b);
        }
        return (this->c < t1.c);
    }
};

Triple get_hash(string s) {
    Triple hash = {0, 0, 0};
    for (int i = 0; i < s.length(); i++) {
        hash.a += (powers1[i] * (s[i] - 'a' + 1)) % MOD1;
        hash.b += (powers2[i] * (s[i] - 'a' + 1)) % MOD2;
        hash.c += (powers3[i] * (s[i] - 'a' + 1)) % MOD3;
        hash.a %= MOD1, hash.b %= MOD2, hash.c %= MOD3;
    }
    return hash;
}

void replace(Triple &hash, int ind, char c1, char c2) {
    hash.a -= (powers1[ind] * (c1 - 'a' + 1)) % MOD1;
    hash.a += (powers1[ind] * (c2 - 'a' + 1)) % MOD1;
    hash.a += 2 * MOD1, hash.a %= MOD1;

    hash.b -= (powers2[ind] * (c1 - 'a' + 1)) % MOD2;
    hash.b += (powers2[ind] * (c2 - 'a' + 1)) % MOD2;
    hash.b += 2 * MOD2, hash.b %= MOD2;

    hash.c -= (powers3[ind] * (c1 - 'a' + 1)) % MOD3;
    hash.c += (powers3[ind] * (c2 - 'a' + 1)) % MOD3;
    hash.c += 2 * MOD3, hash.c %= MOD3;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    const int MX = 1e6;
    powers1.push_back(1), powers2.push_back(1), powers3.push_back(1);
    while (powers1.size() != MX) {
        powers1.push_back((powers1.back() * base) % MOD1);
        powers2.push_back((powers2.back() * base) % MOD2);
        powers3.push_back((powers3.back() * base) % MOD3);
    }
    int N, K;
    cin >> N >> K;
    map<Triple, int> myMap;
    vector<Triple> arr;
    vector<string> strings;
    for (int i = 0; i < N; i++) {
        string s;
        cin >> s;
        strings.push_back(s);
        arr.push_back(get_hash(s));
        myMap[arr.back()]++;
    }
    string best;
    best.assign(1e6, 'z');
    int myMax = -1;
    int cntr = 0;
    for (int i = 0; i < arr.size(); i++) {
        string s = strings[i];
        Triple hash = arr[i];
        int c = myMap[hash];
        for (int ind = 0; ind < s.length(); ind++) {
            for (char ch = 'a'; ch <= 'z'; ch++) {
                if (ch == s[ind]) {
                    continue;
                }
                replace(hash, ind, s[ind], ch);
                if (myMap.count(hash)) {
                    c += myMap[hash];
                }
                hash = arr[i];
            }
        }
        //cout << s << " " << c << '\n';
        if (c == myMax) {
            cntr++;
            best = min(best, s);
        } else if (myMax < c) {
            myMax = c;
            cntr = 1;
            best = s;
        }
    }
    cout << best << '\n';
    cout << cntr << '\n';
}
