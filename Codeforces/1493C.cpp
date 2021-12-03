#include <iostream>
#include <cmath>
#include <vector>
#include <set>
#include <chrono>
#include <random>
#include <queue>
#include <cstdint>
#include <cassert>
#include <bit>
#include <bitset>
#include <map>
#include <list>
#include <stack>
#include <algorithm>

#define ll long long
using namespace std;

string s;

bool good (string ans, int n, int k) {
    if (ans.size() != n) return false;
    map<char,int> oc;
    for (char c: ans) oc[c]++;
    for (auto& p: oc) {
        if (p.second % k != 0) {
            return false;
        }
    }
    return true;
}

void solve () {
    int n, k;
    cin >> n >> k;
    cin >> s;
    if (n % k != 0) {
        cout << -1 << '\n';
        return;
    }
    if (good(s, n, k)) {
        cout << s << '\n';
        return;
    }
    map<char,int> oc;
    for (int i = 0; i < s.length() - 1; i++) {
        oc[s[i]]++;
    }
    for (int len = s.length() - 1; len >= 0; len--) {
        int sum = 0;
        for (pair<char,int> p: oc) {
            sum += (k - p.second % k) % k;
        }
        char st = s[len]; st++;
        for (char c = st; c <= 'z'; c++) {
            int prev = sum;
            sum -= (k - oc[c] % k) % k;
            oc[c]++;
            sum += (k - oc[c] % k) % k;
            if (sum + len <= n) {
                string suf;
                for (auto& p: oc) {
                    p.second = (k - p.second % k) % k;
                    while (p.second--) {
                        suf += p.first;
                    }
                }
                while (suf.length() + len + 1 < n) {
                    suf += 'a';
                }
                sort(suf.begin(), suf.end());
                string pref = "";
                for (int i = 0; i < len; i++) {
                    pref += s[i];
                }
                pref += c;
                assert(good(pref + suf, n, k));
                cout << pref + suf << '\n';
                return;
            }
            oc[c]--;
            sum = prev;
        }
        if (len != 0) {
            oc[s[len - 1]]--;
        }
    }
    cout << "-1\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }

}
