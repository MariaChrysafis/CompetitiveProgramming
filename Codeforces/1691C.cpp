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
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        string s;
        cin >> s;
        int64_t ans = 0;
        for (int i = 1; i < s.length(); i++) {
            ans += 10 * (s[i - 1] - '0') + (s[i] - '0');
        }
        vector<int> v, u;
        for (int i = 0; i < (int)s.length(); i++) {
            if (s[i] == '1') {
                v.push_back((int)s.length() - i - 1);
                u.push_back(i);
            }
        }
        if (!v.empty() && v.back() <= k && s.back() != '1') {
            ans -= 10;
            if (v.back() == (int)s.length() - 1) ans++;
            k -= v.back();
            u.pop_back();
        }
        if (!u.empty() && s.front() != '1' && u.front() <= k && u.front() != (int)s.size() - 1) {
            ans--;
        }
        cout << ans << '\n';
    }
}
