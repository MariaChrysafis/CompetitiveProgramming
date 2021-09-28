#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <fstream>

using namespace std;
int solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<int> > p(n + 1);
    vector<map<int,int> > vec(n + 1);
    for(int i = 0; i <= n; i++) {
        vector<int> v(m);
        for(int j = 0; j < m; j++) {
            cin >> v[j];
            vec[i][v[j]]++;
        }
        p[i] = v;
    }
    vector<vector<int> > ans(n + 1);
    for(int i = 0; i <= n; i++) {
        ans[i].resize(m);
    }
    for(int i = 0; i < m; i++) {
        ans[0][i] = p[0][i];
    }
    bool hasChanged[m];
    for(int i = 0; i < m; i++) {
        hasChanged[i] = false;
    }
    for(int i = 1; i <= n; i++) {
        for(int j = 0; j < m; j++) {
            if(vec[i][ans[i - 1][j]] && hasChanged[j]) {
                vec[i][ans[i - 1][j]]--;
                ans[i][j] = ans[i - 1][j];
            }
        }
        for(int j = 0; j < m; j++) {
            if(!ans[i][j] && vec[i][ans[i - 1][j]] && !hasChanged[j]) {
                vec[i][ans[i - 1][j]]--;
                ans[i][j] = ans[i - 1][j];
            }
        }
        vector<int> left;
        for(pair<int,int> p: vec[i]) {
            while(p.second--) {
                left.push_back(p.first);
            }
        }
        for(int j = 0; j < m; j++) {
            if(!ans[i][j]) {
                ans[i][j] = left.back();
                left.pop_back();
                hasChanged[j] = true;
            }
        }
    }
    int val = 0;
    for(int j = 0; j < m; j++) {
        int prev = ans[0][j];
        int cntr = 0;
        for(int i = 1; i <= n; i++) {
            if(ans[i][j] != prev) {
                cntr++;
            }
            prev = ans[i][j];
        }
        val += max(cntr - 1, 0);
    }
    return val;

}

int main() {
    freopen("haha", "r", stdin);
    int t;
    cin >> t;
    for (int i = 1; i <= t; i++) {
        cout << "Case #" << i << ": ";
        cout << solve();
        cout << '\n';
    }

}
