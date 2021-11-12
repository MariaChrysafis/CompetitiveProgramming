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
#include <map>

#define ll long long

using namespace std;
vector<int> generate_pref (string s) {
    vector<int> pref = {0};
    for (int i = 0; i < s.length(); i++) {
        pref.push_back((s[i] - '0') + pref.back());
    }
    return pref;
}
bool isSorted (string s) {
    string str = s;
    sort(str.begin(), str.end());
    return (str == s);
}
void solve() {
    int n;
    cin >> n;
    string s;
    cin >> s;
    vector<vector<int>> vec;
    while (!isSorted(s)) {
        vector<int> pref = generate_pref(s);
        int myMax = -1;
        int best = 0;
        for (int i = 0; i < s.length(); i++) {
            //[0, i] and [i + 1, s.length() - 1]
            int x = pref[i + 1];
            int y = pref[s.length()] - pref[i + 1];
            y = (int)s.length() - i - 1 - y;
            if (min(x,y) > myMax) {
                myMax = min(x, y);
                best = i;
            }
        }
        vector<int> indices;
        for (int i = 0; i <= best; i++) {
            if(s[i] == '1') indices.push_back(i);
        }
        for (int i = best + 1; i < s.length(); i++) {
            if (s[i] == '0') indices.push_back(i);
        }
        vec.push_back(indices);
        for (int i = 0; i < indices.size() - 1; i++) {
            swap(s[i], s[indices.size() - i - 1]);
        }
        break;
    }
    cout << vec.size() << '\n';
    for (int i = 0; i < vec.size(); i++) {
        cout << vec[i].size() << ' ';
        for (int j: vec[i]) {
            cout << j + 1 << " ";
        }
        cout << '\n';
    }
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
