#include <iostream>
#include <cmath>
#include <vector>
#include <set>
#include <chrono>
#include <random>
#include <queue>
#include <cassert>
#include <map>
#include <algorithm>

#define ll long long
using namespace std;
string remove_trailing (string s) {
    if (s == "0") return s;
    reverse(s.begin(), s.end());
    while (s.back() == '0' && s.size() > 1) {
        s.pop_back();
    }
    reverse(s.begin(), s.end());
    return s;
}
string remove_index (string s, int ind) {
    string ans = "";
    for (int i = 0; i < ind; i++) {
        ans += s[i];
    }
    for (int i = ind + 1; i < s.length(); i++) {
        ans += s[i];
    }
    return ans;
}
string remove_indices (string s, int ind1, int ind2) {
    string ans = "";
    for (int i = 0; i < s.length(); i++) {
        if (i == ind1 || i == ind2) continue;
        ans += s[i];
    }
    return ans;
}
bool comp (string s, string t) {
    if (s.length() == t.length()) {
        return (s < t);
    }
    return (s.length() > t.length());
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string s;
    cin >> s;
    int ans = 0;
    for (char c: s) {
        ans += (c - '0') % 3;
    }
    ans %= 3;
    if (ans == 0) {
        cout << s;
        return 0;
    }
    vector<vector<int>> oc(3);
    for (int i = 0; i < s.length(); i++) {
        oc[(s[i] - '0') % 3].push_back(i);
    }
    set<string> pos;
    for (int i = s.length() - 1; i >= 0; i--) {
        if (pos.size() == 1) break;
        if ((s[i] - '0') % 3 == ans % 3) {
            if (!remove_trailing(remove_index(s, i)).empty()) {
                pos.insert(remove_trailing(remove_index(s, i)) );
                break;
            }
        }
    }
    for (int i = s.length() - 1; i >= 0; i--) {
        if (pos.size() == 2) break;
        for (int j: oc[(ans - (s[i] - '0') + 9) % 3]) {
            if (j <= i) continue;
            //if (((s[i] - '0') + (s[j] - '0')) % 3 == ans % 3) {
                if (!remove_trailing(remove_indices(s, i, j)).empty()) {
                    pos.insert(remove_trailing(remove_indices(s, i, j)) );
                    break;
                }
            //}
        }
    }
    vector<string> vec;
    for (string s: vec) {
        cout << s << endl;
    }
    for (string s: pos) vec.push_back(s);
    sort(vec.begin(), vec.end(), comp);
    if (vec.empty()) cout << "-1\n";
    else cout << vec[0];
}
