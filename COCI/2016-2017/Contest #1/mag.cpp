#include <bits/stdc++.h>
using namespace std;
vector<int> val;
vector<int> parent;
vector<int> dp1, dp2, dp3;
//dp1 is the maximum path that goes down
//dp2 is the maximum path that does not necessarily go down
//dp3 is the maximum path that goes up (straight up)
int get_max (vector<int>& v) {
    if (v.empty()) {
        return 0;
    }
    if (v.size() == 1) {
        return v[0];
    }
    sort(v.begin(), v.end());
    if (!v.empty()) assert(v[0] != 0);
    return v.back() + v[v.size() - 2];
}
void dfs (vector<vector<int> > &adj, int curNode, int prevNode) {
    dp1[curNode] = (val[curNode] == 1);
    for (int i: adj[curNode]) {
        if (i != prevNode) {
            dfs (adj, i, curNode);
            if (val[curNode] == 1 && val[i] == 1) dp1[curNode] = max(dp1[curNode], dp1[i] + 1);
        }
    }
}
void dfs2 (vector<vector<int> > &adj, int curNode, int prevNode) {
    parent[curNode] = prevNode;
    dp2[curNode] = dp1[curNode];
    vector<int> v;
    for (int i: adj[curNode]) {
        if (i != prevNode) {
            dfs2(adj, i, curNode);
            if (dp1[i]) v.push_back(dp1[i]);
        }
    }
    dp2[curNode] = max(dp2[curNode], get_max(v) + 1);
    if (val[curNode] != 1) {
        dp2[curNode] = 0;
    }
}
 
int main() {
    //freopen("input.txt", "r", stdin);
    vector<vector<int> > adj;
    int n;
    cin >> n;
    adj.resize(n), dp1.resize(n), dp2.resize(n), dp3.assign(n, 0), parent.resize(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v), adj[v].push_back(u);
    }
    val.resize(n);
    int myMin = INT_MAX;
    for (int i = 0; i < n; i++) {
        cin >> val[i];
        myMin = min(myMin, val[i]);
    }
    if (myMin >= 2) {
        cout << myMin << "/" << 1;
        return 0;
    }
    dfs(adj, n - 1, n - 1);
    dfs2(adj, n - 1, n - 1);
    queue<int> q;
    q.push(n - 1);
    dp3[0] = (val[0] == 1);
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        if (val[x] != 1) {
            dp3[x] = 0;
        }
        for (int i: adj[x]) {
            if (i != parent[x]) {
                if (val[i] == 1) dp3[i] = max(dp3[i], dp3[x] + 1);
                q.push(i);
            }
        }
    }
    int myMax2 = 0;
    int myMax1 = 0;
    for (int i = 0; i < n; i++) {
        myMax1 = max(myMax1, max(max(dp2[i], dp3[i]), dp1[i]));
        if (val[i] == 2) {
            vector<int> v;
            for (int j: adj[i]) {
                if (j == parent[i]) {
                    if (dp3[j]) v.push_back(dp3[j]);
                } else {
                    if (dp1[j]) v.push_back(dp1[j]);
                }
            }
            myMax2 = max(myMax2, get_max(v));
        }
    }
    myMax2++;
    if (myMax2 > myMax1 * 2) {
        if (myMax2 % 2 == 1) {
            cout << 2 << "/" << myMax2;
        } else {
            cout << 1 << "/" << myMax2/2;
        }
    } else {
        cout << 1 << "/" << myMax1;
    }
 
}
