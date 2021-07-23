#include <vector>
#include <iostream>
#include <cmath>
#include <cassert>
#include <map>
#include <algorithm>
 
using namespace std;
 
void print(vector<int> v) {
    for (int i: v) {
        cout << i << " ";
    }
    cout << endl;
}
 
void print(vector<long long> v) {
    for (long long x: v) {
        cout << x << " ";
    }
    cout << endl;
}
 
void print(vector<char> v) {
    for (char c: v) {
        cout << c << " ";
    }
    cout << endl;
}
 
void print(vector<vector<int>> v) {
    for (vector<int> vec: v) {
        print(vec);
    }
    cout << endl;
}
 
void print(vector<vector<long long>> v) {
    for (vector<long long> vec: v) {
        print(vec);
    }
    cout << endl;
}
 
void print(vector<vector<char>> v) {
    for (vector<char> vec: v) {
        print(vec);
    }
    cout << endl;
}
 
vector<vector<int>> fill(int n, int m, int val) {
    vector<vector<int>> v;
    v.resize(n);
    for (int i = 0; i < n; i++) {
        v[i].resize(m);
        for (int j = 0; j < m; j++) {
            v[i][j] = val;
        }
    }
    return v;
}
 
vector<int> read(int n) {
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    return arr;
}
 
const int INF = 1e9;
vector<int> arr;
vector<vector<int>> maxMoves;
 
struct state {
    int pref, dig;
};
 
bool operator<(state s1, state s2) {
    if (s1.pref == s2.pref) return (s1.dig < s2.dig);
    else return (s1.pref < s2.pref);
}
 
bool operator==(state s1, state s2) {
    return (s1.pref == s2.pref && s1.dig == s2.dig);
}
 
map<state, state> adj;
map<state, bool> important;
vector<int> orig;
vector<state> path;
 
void dfs(state cur) {
    path.push_back(cur);
    if (cur.pref == 0) {
        return;
    }
    dfs(adj[cur]);
}
 
int main() {
    int n;
    cin >> n;
    int d;
    cin >> d;
    orig = read(n);
    //sort(orig.begin(), orig.end());
    vector<vector<double>> fl(n);
    for (int i = 0; i < n; i++) {
        fl[i].resize(10);
        for (int j = 0; j < 10; j++) {
            fl[i][j] = -1;
        }
    }
    maxMoves = fill(n, 10, -1);
    maxMoves[0][orig[0] % 10] = 1;
    fl[0][orig[0] % 10] = log2(orig[0]);
    maxMoves[0][1] = max(maxMoves[0][1], 0);
    fl[0][1] = max(fl[0][1], 0.0);
    for (int i = 1; i < n; i++) {
        for (int j = 0; j <= 9; j++) {
            maxMoves[i][j] = maxMoves[i - 1][j];
            fl[i][j] = fl[i - 1][j];
            adj[{i, j}] = {i - 1, j};
            important[{i, j}] = false;
        }
        for (int j = 0; j <= 9; j++) {
            if (maxMoves[i - 1][j] == -1) {
                continue;
            }
            int dif = (j * orig[i]) % 10;
            double newfl = fl[i - 1][j] + log2(orig[i]);
            if (newfl > fl[i][dif] || (maxMoves[i][dif] < maxMoves[i - 1][j] + 1 && newfl == fl[i][dif])) {
                maxMoves[i][dif] = maxMoves[i - 1][j] + 1;
                adj[{i, dif}] = {i - 1, j};
                fl[i][dif] = newfl;
                important[{i, dif}] = true;
            }
        }
    }
    if (maxMoves[n - 1][d] == -1 || maxMoves[n - 1][d] == 0) {
        cout << "-1\n";
        return 0;
    }
    cout << maxMoves[n - 1][d] << endl;
    dfs({n - 1, d});
    vector<int> ans;
    for (int i = 0; i < path.size(); i++) {
        state st = path[i];
        if (important[st]) {
            ans.push_back(path.size() - i - 1);
        }
    }
    for (int i: ans) {
        cout << orig[i] << " ";
    }
    if (ans.size() != maxMoves[n - 1][d]) {
        cout << orig[0];
    }
 
}
