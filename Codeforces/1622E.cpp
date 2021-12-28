#include <iostream>
#include <vector>
#include <chrono>
#include <cstdint>
#include <algorithm>
using namespace std;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> x(n);
    for (int i = 0; i < x.size(); i++) {
        cin >> x[i];
    }
    vector<string> s(n);
    for (int i = 0; i < s.size(); i++) {
        cin >> s[i];
    }
    int myMax = -1e9;
    vector<pair<int,int>> best;
    for (int i = 0; i < (1 << n); i++) {
        vector<pair<int,int>> c(m);
        for (int j = 0; j < m; j++) {
            c[j].first = 0, c[j].second = j;
        }
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < s[j].length(); k++) {
                if (s[j][k] == '1') {
                    if (i & (1 << j)) c[k].first++;
                    else c[k].first--;
                }
            }
        }
        sort(c.begin(), c.end());
        int cntr = 0;
        for (int j = 0; j < n; j++) {
            if (i & (1 << j)) cntr -= x[j];
            else cntr += x[j];
        }
        for (int j = 0; j < c.size(); j++) {
            cntr += c[j].first * (j + 1);
        }
        if (cntr > myMax) {
            //cout << i << '\n';
            myMax = cntr;
            best = c;
        }
    }
    int ans[m];
    for (int i = 0; i < best.size(); i++) {
        ans[best[i].second] = i;
    }
    for (auto& p: ans) {
        cout << p + 1 << ' ';
    }
    cout << '\n';
    //cout << myMax << '\n';
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
