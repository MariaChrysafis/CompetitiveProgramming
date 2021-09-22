#include <vector>
#include <iostream>
#include <cassert>
#include <cmath>

#define ll long long
using namespace std;

struct tree {
    vector<vector<ll>> adj;
    vector<vector<ll>> dp;
    vector<ll> enter;
    vector<ll> exit;
    vector<ll> sub;
    vector<ll> head;
    ll cntr = 1;
    ll lg2;

    void dfs(int u, int prev) {
        cntr++;
        enter[u] = cntr;
        dp[u][0] = prev;
        for (int i = 1; i <= lg2; i++) {
            dp[u][i] = dp[dp[u][i - 1]][i - 1];
        }
        for (int v: adj[u]) {
            if (v != prev) {
                dfs(v, u);
            }
        }
        cntr++;
        exit[u] = cntr;
    }

    ll dfsForSub(int cur, int prev) {
        int ans = 1;
        for (int i: adj[cur]) {
            if (i != prev) {
                ans += dfsForSub(i, cur);
            }
        }
        return (sub[cur] = ans);
    }

    void dfsForHead(int cur, int prev, int hd) {
        head[cur] = hd;
        for (int i: adj[cur]) {
            if (i != prev) {
                dfsForHead(i, cur, hd);
            }
        }
    }

    bool isAncestor(int u, int v) {
        return (enter[u] <= enter[v] && exit[u] >= exit[v]);
    }

    int leastCommonAncestor(int u, int v) {
        if (isAncestor(u, v)) {
            return u;
        }
        if (isAncestor(v, u)) {
            return v;
        }
        for (int i = lg2; i >= 0; i--) {
            if (!isAncestor(dp[u][i], v)) {
                u = dp[u][i];
            }
        }
        return dp[u][0];
    }

    void read() {
        long long n = adj.size();
        lg2 = ceil(log2(n)) + 1;
        enter.resize(n);
        exit.resize(n);
        adj.resize(n);
        dp.resize(n);
        sub.resize(n);
        head.resize(n);
        for(int i: adj[0]) {
             dfsForHead(i, 0, i);
        }
        for (int i = 0; i < n; i++) {
            dp[i].resize(lg2 + 1);
            enter[i] = exit[i] = -1;
        }
        dfs(0, 0);
        dfsForSub(0, -1);
        int left = 0;
        int right = 0;
        vector<ll> v = {n * (n - 1) / 2}; 
        ll ansr = n * (n - 1) / 2; 
        for (ll i: adj[0]) {
            ansr -= sub[i] * (sub[i] - 1) / 2;
        }
        v.push_back(ansr);
        //cout << ansr << endl;
        bool last = false;
        for (int i = 1; i < n; i++) {
            if (isAncestor(i, left) || isAncestor(i, right)) {

            } else if (isAncestor(left, i)) {
                left = i;
            } else if (isAncestor(right, i)) {
                right = i;
            } else {
                right = left = -1;
            }
            if (left < 0 || right < 0 || leastCommonAncestor(left, right) != 0) {
                for (int j = 1; j < v.size(); j++) {
                    cout << v[j - 1] - v[j] << " ";
                }
                cout << v.back() << " ";
                int x = (int) v.size();
                while (x != n + 1) {
                    cout << 0 << " ";
                    x++;
                }
                cout << '\n';
                return;
            }
            if (right == 0 || left == 0) {
                if (left == 0) {
                    swap(left, right);
                }
                int ans = n - sub[head[left]];
                v.push_back(sub[left] * ans);
                continue;
            }
            v.push_back(sub[left] * sub[right]);
        }
        for (int i = 1; i < v.size(); i++) {
            cout << v[i - 1] - v[i] << " ";
        }
        cout << v.back() << " ";
        cout << '\n';

    }
};

int main() {
    int t;
    cin >> t;
    while (t--) {
        tree myTree;
        int n;
        cin >> n;
        myTree.adj.resize(n);
        for (int i = 0; i < n - 1; i++) {
            int u, v;
            cin >> u >> v;
            myTree.adj[u].push_back(v), myTree.adj[v].push_back(u);
        }
        myTree.read();
    }
}
