#include <vector>
#include <algorithm>
#include <iostream>
#include <set>
#include <cmath>
#include <map>
#include <random>
#include <cassert>
#include <ctime>
#include <cstdlib>
#include <queue>
#include <limits.h>

using namespace std;
const int MOD = 1e9 + 9;
vector<pair<int,int>> vec;
vector<pair<int,int>> jmp;
vector<int> v;
vector<int> id;
void update (int l, int r) {
    for (int i = r; i >= l; i--) {
        if (v[i] + i > r) {
            jmp[i] = {1, i};
        } else {
            jmp[i] = jmp[v[i] + i];
            jmp[i].first++;
        }
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N, M;
    cin >> N >> M;
    v.resize(N);
    for (int i = 0; i < N; i++) {
        cin >> v[i];
    }
    const int sq = sqrt(N) + 1;
    id.resize(N);
    for (int i = 0; i < N; i += sq) {
        vec.push_back({i, i + sq - 1});
        vec.back().second = min(vec.back().second, N - 1);
        for (int j = vec.back().first; j <= vec.back().second; j++) {
            id[j] = i/sq;
        }
    }
    jmp.resize(N);
    for (auto& p: vec) {
        update(p.first, p.second);
    }
    while (M--) {
        int t;
        cin >> t;
        if (t == 0) {
            int a, b;
            cin >> a >> b;
            a--;
            v[a] = b;
            update(vec[id[a]].first, vec[id[a]].second);
        } else {
            int a;
            cin >> a;
            a--;
            pair<int,int> ans = jmp[a];
            while (ans.second + v[ans.second] < N) {
                //cout << ans.first << " ? " << ans.second << '\n';
                ans.first +=  jmp[ans.second + v[ans.second]].first;
                ans.second = jmp[ans.second + v[ans.second]].second;
            }
            cout << ans.second + 1 << " " << ans.first << '\n';
        }
    }
}
