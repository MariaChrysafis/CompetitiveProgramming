#include <cmath>
#include <iostream>
#include <set>
#include <climits>
#include <cstdio>
#include <algorithm>
#include <cassert>
#include <string>
#include <vector>
#include <iomanip>
#include <unordered_map>
#include <type_traits>
#include <bitset>
#include <string>
#include <queue>
#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")
 
#define ll long long
 
#include <map>
 
using namespace std;
bitset<700001> bs;
int solve (vector<int>& v, int x) {
    bs.reset();
    bs.set(0);
    for (int i = 0; i < v.size(); i++) {
        if (i != x) {
            bs = bs | (bs << v[i]);
        }
    }
    return bs.count();
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N;
    cin >> N;
    vector<int> v(N);
    for (int i = 0; i < N; i++) {
        cin >> v[i];
    }
    pair<int,int> p = {-1, -1};
    for (int i = 0; i < N; i++) {
        p = max(p, {solve(v, i), i});
    }
    solve(v, p.second);
    for (int i = 0; i < N; i++) {
        if (i != p.second) {
            bs |= bs >> v[i];
        }
    }
    for (int i = 0; i != -1; i++) {
        if (!bs.test(i)) {
            cout << v[p.second] << " " << i << '\n';
            return 0;
        }
    }
}
