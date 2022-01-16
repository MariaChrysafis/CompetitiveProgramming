#include <vector>
#include <chrono>
#include <iostream>
#include <map>
#include <set>
#include <climits>
#include <cmath>
#include <cassert>
#include <stack>
#include <queue>
#include <algorithm>
#include <string>

#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")

using namespace std;

typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N, K, M;
    cin >> N >> K >> M;
    map<int,vector<int>> oc;
    for (int i = 0; i < N; i++) {
        int x;
        cin >> x;
        oc[x % M].push_back(x);
    }
    for (auto& p: oc) {
        if (p.second.size() >= K) {
            vector<int> ans = p.second;
            cout << "Yes\n";
            for (int i = 0; i < K; i++) {
                cout << ans[i] << ' ';
            }
            cout << '\n';
            return 0;
        }
    }
    cout << "No\n";
}
