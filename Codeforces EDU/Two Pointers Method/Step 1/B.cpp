#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <queue>
#include <cassert>

using namespace std;

void solve () {
    int n, m;
    cin >> n >> m;
    vector<int> v1(n), v2(m);
    for(int i = 0; i < n; i++) cin >> v1[i];
    for(int i = 0; i < m; i++) cin >> v2[i];
    int pntr = 0;
    for (int i = 0; i < m; i++) {
        while(pntr != n && v1[pntr] < v2[i]) {
            pntr++;
        }
        cout << pntr << " ";
    }
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();

}
