#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <unordered_set>
#include <algorithm>
#include <random>
#include <chrono>
#include <queue>
 
using namespace std;
 
void solve(int tc) {
    int n, m;
    cin >> n >> m;
    vector<vector<char>> v(n);
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        v[i].resize(n);
        for (int j = 0; j < n; j++) {
            v[i][j] = s[j];
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (v[i][j] == v[j][i] && i != j) {
                cout << "YES\n";
                for (int x = 0; x <= m; x++) {
                    if (x % 2 == 0) {
                        cout << i + 1 << " ";
                    } else {
                        cout << j + 1 << " ";
                    }
                }
                return;
            } else if (i != j && v[i][j] != v[j][i] && m % 2 == 1) {
                cout << "YES\n";
                for (int x = 0; x <= m; x++) {
                    if (x % 2 == 0) {
                        cout << i + 1 << " ";
                    } else {
                        cout << j + 1 << " ";
                    }
                }
                return;
            }
        }
    }
    map<int, vector<int>> myMap[2];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) continue;
            myMap[(v[i][j] - 'a')][i].push_back(j);
        }
    }
    if(n == 2){
        cout << "NO";
        return;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) continue;
            vector<int> vec = myMap[(v[i][j] - 'a')][j];
            for (int k: vec) {
                //cout << i << " " << j << " " << k << endl;
                if (j == k || i == k) continue;
                if (v[k][j] == v[j][i] && v[i][j] == v[j][k]) {
                    cout << "YES\n";
                    if ((m / 2) % 2 == 0) {
                        for (int x = 0; x <= m; x++) {
                            if (x % 2 == 0) {
                                cout << j + 1 << ' ';
                            } else {
                                if (x % 4 == 1) cout << k + 1 << ' ';
                                else cout << i + 1 << ' ';
                            }
                        }
                    } else {
                        for (int x = 0; x <= m; x++) {
                            if (x % 2 == 1) {
                                cout << j + 1 << ' ';
                            } else {
                                if (x % 4 == 0) cout << i + 1 << ' ';
                                else cout << k + 1 << ' ';
                            }
                        }
                    }
                    return;
                }
            }
        }
    }
    cout << "NO";
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    for (int tc = 0; tc < t; tc++) {
        solve(tc);
        cout << endl;
    }
}
