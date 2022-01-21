#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>
#include <map>
#include <algorithm>
#include <set>
#include <queue>

using namespace std;

typedef long long ll;

string remove_dup (string s) {
    string str;
    str += s[0];
    for (int i = 1; i < s.length(); i++) {
        if (s[i] == str.back()) {
            continue;
        }
        str += s[i];
    }
    return str;
}

string remap (string s) {
    set<char> mySet;
    for (char c: s) {
        mySet.insert(c);
    }
    map<char,char> myMap;
    char cur = 'a';
    for (char c: mySet) {
        myMap[c] = cur++;
    }
    string str;
    for (int i = 0; i < s.length(); i++) {
        str += myMap[s[i]];
    }
    return str;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N, M;
    cin >> N >> M;
    string s;
    cin >> s;
    s = remap(remove_dup(s));
    N = s.length();
    int deg[M][M];
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < M; j++) {
            deg[i][j] = 0;
        }
    }
    for (int i = 1; i < s.length(); i++) {
        deg[s[i - 1] - 'a'][s[i] - 'a']++;
        deg[s[i] - 'a'][s[i - 1] - 'a']++;
    }
    int dp[(1 << M)];
    for (int i = 0; i < (1 << M); i++) {
        if (i == 0) {
            dp[0] = 0;
            continue;
        }
        dp[i] = 1e9;
        int cntr = 0;
        for (int j = 0; j < M; j++) {
            for (int k = j; k < M; k++) {
                if ((bool)(i & (1 << j)) ^ (bool)(i & (1 << k))) {
                    cntr += deg[j][k];
                }
            }
        }
        for (int x = 0; x < M; x++) {
            if (i & (1 << x)) {
                dp[i] = min(dp[i], dp[i ^ (1 << x)] + cntr);
            }
        }
    }
    cout << dp[(1 << M) - 1];
}
