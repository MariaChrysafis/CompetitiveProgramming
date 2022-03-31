#include <cmath>
#include <iostream>
#include <set>
#include <climits>
#include <cstdio>
#include <algorithm>
#include <cassert>
#include <string>
#include <vector>
#include <iomanip>
#include <unordered_map>
#include <type_traits>
#include <string>
#include <queue>
#define ll long long
#include <map>
using namespace std;
bool canGet (string s, string t) {
    //can we get string s to look like string t by just removing some characters?
    if (s.substr(0, s.length() - 1) == t) {
        return true;
    }
    int ps = 0;
    int pt = 0;
    while (ps < s.length() && pt < t.length()) {
        if (s[ps] == t[pt]) {
            ps++, pt++;
            continue;
        }
        ps++;
    }
    //cout << ps << " " << pt << '\n';
    return (ps == s.length() && pt == t.length());
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    string s;
    cin >> s;
    if (n % 2 == 0) {
        cout << "NOT POSSIBLE";
        return 0;
    }
    string s1 = s.substr(0, s.length()/2);
    string s2 = s.substr(s.length()/2, s.length() - s.length()/2);

    string t1 = s.substr(0, (s.length() + 1)/2);
    string t2 = s.substr((s.length() + 1)/2, s.length() - (s.length() + 1)/2);
    //cout << t1 << " " << t2 << endl;
    set<string> ans;
    if (canGet(s2, s1)) {
        ans.insert(s1);
    }
    if (canGet(t1, t2)) {
        ans.insert(t2);
    }
    if (ans.empty()) {
        cout << "NOT POSSIBLE";
        return 0;
    }
    if (ans.size() >= 2) {
        cout << "NOT UNIQUE";
        return 0;
    }
    cout << *ans.rbegin();
}
