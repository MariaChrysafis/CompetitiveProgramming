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

#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")

using namespace std;

typedef long long ll;

void solve () {
    int n, m;
    cin >> n >> m;
    //find the center squares
    queue<pair<pair<int,int>,int>> q;
    if (n % 2 == 1 && m % 2 == 1) {
        q.push({{n/2, m/2}, 1});
    } else if (n % 2 == 1 && m % 2 == 0) {
        q.push({{n/2, m/2}, 1});
        q.push({{n/2, m/2 - 1}, 1});
    } else if (n % 2 == 0 && m % 2 == 1) {
        q.push({{n/2, m/2}, 1});
        q.push({{n/2 - 1, m/2}, 1});
    } else if (n % 2 == 0 && m % 2 == 0) {
        q.push({{n / 2, m / 2 - 1}, 1});
        q.push({{n / 2 - 1, m / 2 - 1}, 1});
        q.push({{n / 2, m / 2}, 1});
        q.push({{n / 2 - 1, m / 2}, 1});
    }
    map<pair<int,int>,bool> hasVisited;
    map<int,int> oc;
    while (!q.empty()) {
        pair<pair<int,int>,int> p = q.front();
        q.pop();
        if (hasVisited[p.first]) {
            continue;
        }
        hasVisited[p.first] = true;
        //cout << p.second << '\n';
        oc[p.second]++;
        int x = p.first.first;
        int y = p.first.second;
        for (int dx = -1; dx <= 1; dx++) {
            for (int dy = -1; dy <= 1; dy++) {
                if (x + dx >= 0 && x + dx < n && y + dy >= 0 && y + dy < m && abs(dx) + abs(dy) == 1) {
                    //cout << x + dx << " " << y + dy << " | " << x << " " << y << '\n';
                    q.push({{x + dx, y + dy}, p.second + 1});
                }
            }
        }
    }
    vector<int> val;
    for (auto& p: oc) {
        val.push_back(p.second);
    }
    for (int i = 1; i < val.size(); i++) {
        val[i] += val[i - 1];
    }
    vector<int> vec(n * m);
    for (int i = 0; i < vec.size(); i++) {
        vec[i] = 0;
    }
    for (int i: val) {
        if (i < vec.size()) {
            vec[i]++;
        }
    }
    for (int i = 1; i < vec.size(); i++) {
        vec[i] += vec[i - 1];
    }
    int maxDist = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            maxDist = max(abs(i - n/2) + abs(j - m/2), maxDist);
        }
    }
    for (int i = 0; i < vec.size(); i++) {
        cout << vec[i] + maxDist << ' ';
    }
    cout << '\n';
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}
