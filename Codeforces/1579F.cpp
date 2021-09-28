#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <queue>
#include <cmath>
#include <cassert>

#define ll long long

#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")

using namespace std;

int gcd(int a, int b) {
    if (min(a, b) == 0) return max(a, b);
    else return gcd(max(a, b) % min(a, b), min(a, b));
}

void solve() {
    int n;
    cin >> n;
    int d;
    cin >> d;
    vector<int> v(n);
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        v[i] = x;
    }
    for (int j = 0; j < gcd(n, d); j++) {
        bool fine = false;
        for (int i = j; i < n; i += gcd(n, d)) {
            if (v[i] == 0) {
                fine = true;
            }
        }
        if (!fine) {
            cout << "-1\n";
            return;
        }
    }
    vector<int> adj(n);
    vector<int> inv_adj(n);
    vector<int> dist(n);
    for(int i = 0; i < n; i++) {
        dist[i] = 1e9;
    }
    for(int i = 0; i < n; i++) {
        adj[i] = (i + n - d) % n;
        inv_adj[(i + n - d) % n] = i;
    }
    queue<pair<int,int>> q;
    for(int i = 0; i < v.size(); i++) {
        if(v[i] == 0) {
            q.push(make_pair(i, 0));
            dist[i] = 0;
        }
    }
    while(!q.empty()) {
        int x = q.front().first;
        int d = q.front().second;
        q.pop();
        if(dist[inv_adj[x]] == 1e9) {
            q.push(make_pair(inv_adj[x], d + 1));
            dist[inv_adj[x]] = d + 1;
        }
    }
    int myMax = 0;
    for(int i = 0; i < n; i++) {
        myMax = max(myMax, dist[i]);
    }
    cout << myMax << '\n';
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
