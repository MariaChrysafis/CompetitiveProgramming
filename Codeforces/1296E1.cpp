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
int MEX (set<int>& s, int strt) {
    for (int i = strt; i <= 3e5; i++) {
        if (!s.count(i)) {
            return i;
        }
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    string s;
    cin >> s;
    set<int> used[27]; //what's used and >= 'a'
    int mex[27]; //mex of elements in used[i]
    for (int i = 0; i < 27; i++) {
        mex[i] = 1;
    }
    vector<int> v;
    for (int i = 0; i < s.length(); i++) {
        int ans = mex[s[i] - 'a' + 1];
        v.push_back(ans);
        for (char j = 'a'; j <= s[i]; j++) {
            if (used[j - 'a'].count(ans)) continue;
            used[j - 'a'].insert(ans);
            if (mex[j - 'a'] == ans) {
                used[j - 'a'].insert(ans);
                mex[j - 'a'] = MEX(used[j - 'a'], ans);
            }
        }
    }
    int myMax = 0;
    for (int i: v) {
        myMax = max(myMax, i);
    }
    if (myMax > 2) {
        cout << "NO\n";
        return 0;
    }
    cout << "YES\n";
    for (int i: v) {
        cout << i - 1;
    }
}
