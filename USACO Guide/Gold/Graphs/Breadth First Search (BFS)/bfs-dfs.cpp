#include <vector>
#include <iostream>
#include <cassert>
#include <cmath>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <climits>
#include <unordered_map>
#include <set>
#include <algorithm>
#include <iomanip>

using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N;
    cin >> N;
    vector<int> bfs(N),  dfs(N);
    for (int i = 0; i < N; i++) {
        cin >> bfs[i];
    }
    for (int i = 0; i < N; i++) {
        cin >> dfs[i];
    }
    if (bfs[1] != dfs[1]) {
        cout << -1;
        return 0;
    }
    cout << 2 * N - 3 << endl;
    for (int i = 1; i < N; i++) {
        cout << 1 << " " << bfs[i] << '\n';
    }
    for (int i = 2; i < N; i++) {
        cout << dfs[i] << " " << dfs[i - 1] << '\n';
    }
}
