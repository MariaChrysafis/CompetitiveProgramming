#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <queue>
#include <cassert>

using namespace std;
vector<int> secret = {2, 1, 7, 5, 6};
int get(vector<int> v) {
    int XOR = 0;
    for(int i: v) {
        XOR ^= secret[i - 1];
    }
    return XOR;
}
int queries = 0;
int n, k;
long long query(vector<int> v) {
    assert(v.size() == k);
    queries++;
    assert(queries <= 500);
    cout << "? ";
    for(int i: v) {
        cout << i << " ";
        //assert(i <= 500);
    }
    cout << endl;
    fflush(stdout);
    //return get(v);
    long long x;
    cin >> x;
    return x;
}
struct Graph{
    vector<vector<int>> adj;
    void read() {
        adj.resize(n + 1);
        for(int c = 0; c <= n; c++) {
            for(int i = 0; i <= k; i++) {
                if(i <= n - c && k - i <= c) {
                    int to = c + i - (k - i);
                    adj[c].push_back(to);
                }
            }
        }
        queue<int> q;
        vector<int> par(n + 1), dist(n + 1);
        map<int,bool> hasVisited;
        q.push(0);
        dist[0] = 0;
        par[0] = -1;
        hasVisited[0] = true;
        while(!q.empty()) {
            int x = q.front();
            q.pop();
            for(int i: adj[x]) {
                if(hasVisited[i]) {
                    continue;
                }
                q.push(i);
                par[i] = x;
                hasVisited[i] = true;
            }
        }
        if(!hasVisited[n]) {
            cout << "-1\n";
            return;
        }
        vector<int> path = {n};
        int cur = n;
        while(cur != 0) {
            cur = par[cur];
            path.push_back(cur);
        }
        reverse(path.begin(), path.end());
        vector<int> even, odd;
        for(int i = 1; i <= n; i++) {
            even.push_back(i);
        }
        long long ans = 0;
        for(int i = 1; i < path.size(); i++) {
            int taken = (path[i] + k - path[i - 1])/2;
            assert(taken >= 0 && taken <= k);
            vector<int> vec;
            vector<int> rem_even, rem_odd;
            assert(even.size() >= taken);
            assert(odd.size() >= k - taken);
            for(int j = (int)even.size() - 1; j >= (int)even.size() - taken; j--) {
                vec.push_back(even[j]), rem_even.push_back(even[j]);
            }
            for(int j = (int)odd.size() - 1; j >= (int)odd.size() - (k - taken); j--) {
                vec.push_back(odd[j]), rem_odd.push_back(odd[j]);
            }
            int dum = taken;
            while(dum--){
                assert(even.size() >= 0);
                even.pop_back();
            }
            dum = k - taken;
            while(dum--) {
                assert(odd.size() >= 0);
                odd.pop_back();
            }
            for(int j: rem_odd) {
                even.push_back(j);
            }
            for(int j: rem_even) {
                odd.push_back(j);
            }
            ans ^= query(vec);
        }
        cout << "! " << ans << endl;
        fflush(stdout);

    }
};

void solve () {
    Graph g;
    cin >> n >> k;
    g.read();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();

}
