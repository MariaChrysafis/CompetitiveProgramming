#include <cmath>
#include <cassert>
#include <iostream>
#include <set>
#include <climits>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <type_traits>
#include <string>
#include <queue>
#include <map>
#include <stack>

using namespace std;
int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N, X;
    cin >> N >> X;
    vector<pair<int,int>> vec(N);
    for (int i = 0; i < N; i++) {
        cin >> vec[i].first >> vec[i].second;
    }
    vector<bool> prev, cur;
    prev.assign(X + 1, false);
    cur.assign(X + 1, false);
    prev[0] = true;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j <= X; j++) {
            if (j >= vec[i].first && prev[j - vec[i].first]) {
                cur[j] = true;
            }
            if (j >= vec[i].second && prev[j - vec[i].second]) {
                cur[j] = true;
            }
        }
        prev = cur;
        cur.assign(X + 1, false);
    }
    string ans = prev.back() ? "Yes" : "No";
    cout << ans;
}
