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
#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    freopen("word.in", "r", stdin);
    freopen("word.out", "w", stdout);
    int N, M;
    cin >> N >> M;
    string cur_line = ""; int len = 0;
    for (int i = 0; i < N; i++) {
        string s;
        cin >> s;
        if (s.length() + len > M) {
            cout << cur_line << '\n';
            cur_line = s, len = s.length();
        } else {
            if (!cur_line.empty()) {
                cur_line += ' ';
            }
            cur_line += s, len += s.length();
        }
    }
    cout << cur_line << '\n';
}
