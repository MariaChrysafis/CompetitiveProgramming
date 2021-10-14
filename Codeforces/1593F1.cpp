#include <bits/stdc++.h>

#pragma GCC optimize("Ofast")

using namespace std;

struct Node {
    int ind;
    int a, b;
    int dif;

    bool operator<(Node a1) const {
        if (a1.ind != ind) {
            return a1.ind < ind;
        }
        if (a1.a != a) {
            return a1.a < a;
        }
        if (a1.b != b) {
            return a1.b < b;
        }
        if (a1.dif != dif) {
            return a1.dif < dif;
        }
        return false;
    }

    bool operator==(const Node a1) const {
        return (a1.ind == ind && a1.a == a && a1.b == b && a1.dif == dif);
    }

    void println() {
        cout << a << " " << b << endl;
    }
};

void solve() {
    int n, A, B;
    cin >> n >> A >> B;
    string s;
    cin >> s;
    bool dp[n + 1][A][B][100];
    pair<Node, int> myMap[n + 1][A][B][100];
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j < A; j++) {
            for (int k = 0; k < B; k++) {
                for (int l = 0; l < 100; l++) {
                    dp[i][j][k][l] = 0;
                }
            }
        }
    }
    dp[0][0][0][50] = 1;
    for (int i = 1; i <= n; i++) {
        int dig = (s[i - 1] - '0');
        for (int j = 0; j < A; j++) {
            for (int k = 0; k < B; k++) {
                for (int dif = 50 - i - 1; dif <= 50 + i + 1; dif++) {
                    if (dp[i - 1][j][k][dif - 1] > 0) {
                        Node nxt = {i - 1, j, k, dif - 1};
                        myMap[i][j][(10 * k + dig) % B][dif] = make_pair(nxt, 1);
                        dp[i][j][(10 * k + dig) % B][dif] =
                                dp[i][j][(10 * k + dig) % B][dif] || dp[i - 1][j][k][dif - 1];
                    }
                    if (dp[i - 1][j][k][dif + 1] > 0) {
                        Node nxt = {i - 1, j, k, dif + 1};
                        myMap[i][(10 * j + dig) % A][k][dif] = make_pair(nxt, 0);
                        dp[i][(10 * j + dig) % A][k][dif] =
                                dp[i][(10 * j + dig) % A][k][dif] || dp[i - 1][j][k][dif + 1];
                    }
                }
            }
        }
    }
    int best = -1;
    int bestVal = INT_MAX;
    for (int dif = 0; dif < 100; dif++) {
        if (dp[n][0][0][dif] > 0 && abs(dif - 50) < bestVal && abs(dif - 50) != n) {
            bestVal = abs(dif - 50);
            best = dif;
        }
    }
    if (best == -1) {
        cout << "-1\n";
        return;
    }
    Node cur = {n, 0, 0, best};
    string str = "";
    while (n--) {
        int id = myMap[cur.ind][cur.a][cur.b][cur.dif].second;
        if (id == 0) str += "R";
        else str += "B";
        cur = myMap[cur.ind][cur.a][cur.b][cur.dif].first;
    }
    reverse(str.begin(), str.end());
    cout << str << endl;
    return;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}
