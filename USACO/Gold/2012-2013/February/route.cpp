

   
#include <cmath>
#include <iostream>
#include <set>
#include <climits>
#include <algorithm>
#include <cassert>
#include <vector>
#include <iomanip>
#include <unordered_map>
#include <type_traits>
#include <string>
#include <queue>
#include <map>

#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")

using namespace std;
#define ll long long
int main() {
    freopen("route.in", "r", stdin);
    freopen("route.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N, M, R;
    cin >> N >> M >> R;
    vector<int> values1(N), values2(M);
    for (int i = 0; i < N; i++) {
        cin >> values1[i];
    }
    for (int i = 0; i < M; i++) {
        cin >> values2[i];
    }
    vector<pair<int,int>> vec(R);
    for (int i = 0; i < R; i++) {
        cin >> vec[i].first >> vec[i].second;
        vec[i].first--, vec[i].second--;
    }
    sort(vec.begin(), vec.end());
    int myMax = 0;
    int dp1[N], dp2[M];
    for (int i = 0; i < N; i++) {
        dp1[i] = values1[i], myMax = max(myMax, dp1[i]);
    }
    for (int i = 0; i < M; i++) {
        dp2[i] = values2[i], myMax = max(myMax, dp2[i]);
    }
    //reverse(vec.begin(), vec.end());
    for (int i = 0; i < vec.size(); i++) {
        int v1 = vec[i].first;
        int v2 = vec[i].second;
        int d1 = dp1[v1]; int d2 = dp2[v2];
        dp1[v1] = max(d1, d2 + values1[v1]);
        dp2[v2] = max(d2, d1 + values2[v2]);
        myMax = max(max(dp1[v1], dp2[v2]), myMax);
    }
    cout << myMax;
}
