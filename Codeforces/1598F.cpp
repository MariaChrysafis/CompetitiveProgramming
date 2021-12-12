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
using namespace std;
int conv (char c) {
    if (c == '(') return 1;
    return -1;
}
struct String {
    vector<vector<int>> oc;
    int pref;
    int min_pref;
};
String process (string s) {
    String ans;
    int sum = 0;
    ans.min_pref = 0;
    int i = 0;
    ans.oc.resize(s.length() + 400000);
    for (char c: s) {
        sum += conv(c);
        ans.oc[sum + 400000].push_back(i++);
        ans.min_pref = min(ans.min_pref, sum);
    }
    ans.pref = sum;
    return ans;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    vector<String> vec;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        vec.push_back(process(s));
    }
    int pref[(1 << n)];
    pref[0] = 0;
    for (int i = 1; i < (1 << n); i++) {
        for (int j = 0; j < n; j++) {
            if ((1 << j) & i) {
                pref[i] = pref[i ^ (1 << j)] + vec[j].pref;
            }
        }
    }
    int dp[(1 << n)];
    dp[0] = 0;
    int myMax = 0;
    for (int i = 1; i < (1 << n); i++) {
        dp[i] = -1e9;
        if (pref[i] < 0) continue;
        for (int j = 0; j < n; j++) {
            if ((1 << j) & i) {
                if (vec[j].min_pref + pref[i ^ (1 << j)] < 0) {
                    continue;
                }
                dp[i] = max(dp[i], dp[i ^ (1 << j)] + (int)vec[j].oc[-pref[i ^ (1 << j)] + 400000].size());
            }
        }
        myMax = max(myMax, dp[i]);
    }
    for (int i = 0; i < (1 << n); i++) {
        if (dp[i] < 0) continue;
        for (int j = 0; j < n; j++) {
            if (!((1 << j) & i)) {
                if (vec[j].oc[-pref[i] + 400000].size() + dp[i] <= myMax) {
                    continue;
                }
                if (vec[j].min_pref + pref[i] >= 0) {
                    continue;
                }
                int ans = dp[i];
                int ind = vec[j].oc[-pref[i] - 1 + 400000][0];
                int l = 0;
                int r = vec[j].oc[-pref[i] + 400000].size() - 1;
                while (l != r) {
                    int m = (l + r + 1)/2;
                    if (vec[j].oc[-pref[i] + 400000][m] < ind) {
                        l = m;
                    } else {
                        r = m - 1;
                    }
                }
                if (vec[j].oc[-pref[i] + 400000][0] > ind) {
                    continue;
                }
                ans += l + 1;
                myMax = max(myMax, ans);
            }
        }
    }

    cout << myMax;
}
