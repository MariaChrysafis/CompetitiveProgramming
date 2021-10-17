/*
 * 8 2 12
1 2 4 2 1 3 5 6 2 3 6 4
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <cmath>
#include <iomanip>
#include <map>
#include <queue>
 
using namespace std;
int N, D, M;
vector<vector<int>> myMap;
vector<int> days;
pair<bool, vector<vector<int>>> valid (int machines) {
    queue<pair<int,int>> q;
    vector<vector<int>> ans;
    for (int i = 1; i <= N; i++) {
        int k = machines;
        ans.push_back((vector<int>){});
        for (int j = 0; j < myMap[i].size(); j++) {
            q.push({i, myMap[i][j]});
        }
        while(k--) {
            if (q.empty()) {
                break;
            }
            if (i - q.front().first > D) {
                return {false, {}};
            }
            ans.back().push_back(q.front().second + 1);
            q.pop();
        }
    }
    if (!q.empty()) return {false, {}};
    return {true, ans};
}
int binSearch (int l, int r) {
    int m = (l + r)/2;
    if (l == r) {
        return l;
    }
    if (valid(m).first) {
        return binSearch(l, m);
    } else {
        return binSearch(m + 1, r);
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> N >> D >> M;
    myMap.resize(N + 1);
    for (int i = 0; i < M; i++) {
        int x;
        cin >> x;
        days.push_back(x);
        myMap[x].push_back(i);
    }
    cout << binSearch(0, M) << endl;
    auto p = valid (2);
    vector<vector<int>> ans = p.second;
    for (int i = 0; i < N; i++) {
        if (i >= (int)ans.size()) {
            cout << 0;
            if (i != N) cout << endl;
            continue;
        }
        for (int j: ans[i]) {
            cout << j << " ";
        }
        cout << 0;
        if (i != N) cout << endl;
    }
}
