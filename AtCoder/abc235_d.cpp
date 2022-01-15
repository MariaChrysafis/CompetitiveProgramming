#include <vector>
#include <chrono>
#include <iostream>
#include <map>
#include <set>
#include <climits>
#include <cmath>
#include <cassert>
#include <stack>
#include <queue>
#include <algorithm>
#include <string>

#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")

using namespace std;

typedef long long ll;

void leftrotate(string &s, int d) {
    reverse(s.begin(), s.begin() + d);
    reverse(s.begin() + d, s.end());
    reverse(s.begin(), s.end());
}

void rightrotate(string &s, int d) {
    leftrotate(s, s.length() - d);
}

int rev(ll x) {
    if (x < 10) return x;
    if (x % 10 == 0) return x;
    string s = to_string(x);
    rightrotate(s, 1);
    return stoi(s);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int A, N;
    cin >> A >> N;
    queue<pair<int,int>> q;
    q.push({1, 0});
    vector<bool> cnt;
    cnt.assign((int)1e6, false);
    //s.insert(1);
    while (!q.empty()) {
        pair<int,int> p = q.front();
        q.pop();
        if (to_string(p.first).length() > to_string(N).length()) continue;
        if (cnt[p.first]) continue;
        if (p.first == N) {
            //cout << p.first << " " << p.second << '\n';
            cout << p.second << '\n';
            return 0;
        }
        //cout << p.first << " " << p.second << '\n';
        cnt[p.first] = true;
        q.push({p.first * A, p.second + 1});
        q.push({rev(p.first), p.second + 1});
    }
    cout << -1;
}
