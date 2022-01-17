#include <vector>
#include <chrono>
#include <iostream>
#include <map>
#include <set>
#include <climits>
#include <cmath>
#include <cassert>
#include <iomanip>
#include <stack>
#include <unordered_map>
#include <queue>
#include <algorithm>
#include <string>

#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")

using namespace std;

typedef long long ll;

vector<string> vec;

bool valid (string pref, string s) {
    int cntr = 0;
    for (int i = 0; i < pref.size(); i++) {
        if (pref[i] != s[i]) {
            cntr++;
        }
    }
    vector<int> oc;
    oc.assign(26, 0);
    for (int i = 0; i < s.size(); i++) {
        oc[s[i] - 'a']++;
    }
    int val = 0;
    for (int i: oc) {
        if (i >= 2) {
            val++;
        }
    }
    if (val < 1 && s == pref) {
        return false;
    }
    for (int i = 0; i < pref.size(); i++) {
        oc[pref[i] - 'a']--;
        if (oc[pref[i] - 'a'] < 0) {
            return false;
        }
    }
    return (cntr <= 2);
}

vector<string> res;

void rec (string cur) {
    if (!res.empty()) {
        return;
    }
    for (string s: vec) {
        if (!valid(cur, s)) {
            return;
        }
    }
    if (cur.size() == vec[0].size()) {
        res.push_back(cur);
        return;
    }
    for (char c = 'a'; c <= 'z'; c++) {
        rec(cur + c);
    }
}

bool valid (string s) {
    for (string str: vec) {
        if (!valid(s, str)) {
            return false;
        }
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N, K;
    cin >> N >> K;
    vec.resize(N);
    for (int i = 0; i < N; i++) {
        cin >> vec[i];
        K = vec[i].length();
    }
    //cout << "YES\nn";
    for (string s: vec) {
        if (valid(s)) {
            cout << s;
            return 0;
        }
    }
    vector<int> pos;
    for (string s: vec) {
        for (string t: vec) {
            for (int k = 0; k < s.length(); k++) {
                if (s[k] != t[k]) {
                    pos.push_back(k);
                }
            }
        }
    }
    if (pos.empty()) {
        for (int i = 0; i < K; i++) {
            pos.push_back(i);
        }
    }
    srand(time(nullptr));
    int t = 40;
    while (t--) {
        for (string s: vec) {
            int x = pos[rand() % pos.size()];
            int y = pos[rand() % pos.size()];
            swap(s[x], s[y]);
            if (valid(s)) {
                cout << s;
                return 0;
            }
            swap(s[x], s[y]);
        }
    }
    if (N <= 10) {
        cout << "-1\n";
        return 0;
    }
    rec("");
    if (res.empty()) {
        cout << "-1\n";
        return 0;
    }
    cout << res.back() << '\n';

}
