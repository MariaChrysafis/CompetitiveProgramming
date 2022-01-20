#include <iostream>
#include <vector>
#include <cassert>
using namespace std;
const int MAX = 5e5 + 10;
const int LG = 20;
vector<int> st[MAX];
int dp[MAX][LG]; //dp[i][j] how far can we cover if we contain i and have at most 2^j intervals
int query (int u, int v) {
    int cur = u;
    int cntr = 0;
    for (int i = LG - 1; i >= 0; i--) {
        if (dp[cur][i] < v) {
            cur = dp[cur][i];
            cntr += (1 << i);
        }
    }
    if (dp[cur][0] < v) {
        return -1;
    }
    return cntr + 1;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N, M;
    cin >> N >> M;
    for (int i = 0; i < N; i++) {
        int x, y;
        cin >> x >> y;
        x++, y++;
        st[x].push_back(y);
    }
    dp[0][0] = 0;
    for (int i = 1; i < MAX; i++) {
        dp[i][0] = max(dp[i - 1][0], i);
        for (int j: st[i]) {
            dp[i][0] = max(dp[i][0], j);
        }
    }
    for (int j = 1; j < LG; j++) {
        for (int i = 0; i < MAX; i++) {
            dp[i][j] = dp[dp[i][j - 1]][j - 1];
        }
    }
    while (M--) {
        int u, v;
        cin >> u >> v;
        u++, v++;
        assert(u <= v);
        cout << query(u, v) << '\n';
    }
}
