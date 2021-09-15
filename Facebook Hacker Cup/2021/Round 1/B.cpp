#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

const int MOD = 1e9 + 7;
void solve() {
    int n, m, a, b;
    cin >> n >> m >> a >> b;
    int arr[n][m];
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            arr[i][j] = 1000;
            if(i == n - 1){
                arr[i][j] = 1;
                continue;
            }
            if(j == m - 1 || j == 0){
                arr[i][j] = 1;
            }
        }
    }
    arr[0][0] = a - n - m + 2;
    arr[0][m - 1] = b - n - m + 2;
    if(a - n - m + 2 <= 0){
        cout << "Impossible";
        return;
    }
    if(b - n - m + 2 <= 0){
        cout << "Impossible";
        return;
    }
    cout << "Possible\n";
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            cout << arr[i][j] << " ";
        }
        if(i != n - 1) cout << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    for (int i = 1; i <= t; i++) {
        cout << "Case #" << i << ": ";
        solve();
        if(i != t) cout << '\n';
    }

}
