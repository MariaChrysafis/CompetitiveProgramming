#include <bits/stdc++.h>
using namespace std;
void transpose (vector<vector<int> > & arr) {
    vector<vector<int> > a(arr[0].size());
    for (int i = 0; i < a.size(); i++) {
        a[i].resize(arr.size());
        for (int j = 0; j < arr.size(); j++) {
            a[i][j] = arr[j][i];
        }
    }
    arr = a;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        vector<vector<int> > arr(n);
        for (int i = 0; i < n; i++) {
            arr[i].resize(m);
            for (int j = 0; j < m; j++) {
                cin >> arr[i][j];
            }
        }
        int myMax = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                pair<int,int> p = make_pair(i, j);
                int ans = 0;
                int x = 0;
                while (p.first - x >= 0 && p.second - x >= 0) {
                    ans += arr[p.first - x][p.second - x];
                    x++;
                }
                x = 1;
                while (p.first + x < n && p.second - x >= 0) {
                    ans += arr[p.first + x][p.second - x];
                    x++;
                }
                x = 1;
                while (p.first - x >= 0 && p.second + x < m) {
                    ans += arr[p.first - x][p.second + x];
                    x++;
                }
                x = 1;
                while (p.first + x < n && p.second + x < m) {
                    ans += arr[p.first + x][p.second + x];
                    x++;
                }
                myMax = max(myMax, ans);
            }
            //cout << '\n';
        }
        cout << myMax << '\n';
        
    }
}
