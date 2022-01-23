#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <map>
#include <algorithm>
#include <climits>
#include <cstring>
#include <set>
#include <queue>
#include <stack>
#include <list>
#include <cstring>

using namespace std;
typedef long long ll;

struct Solver {
    const static int LOG_A = 17;

    int basis[LOG_A];

    int sz = 0;

    Solver() {
        for (int i = 0; i < LOG_A; i++) {
            basis[i] = 0;
        }
    }

    void insertVector(int mask) {
        for (int i = 0; i < LOG_A; i++) {
            if ((mask & 1 << i) == 0) {
                continue;
            }
            if (!basis[i]) {
                basis[i] = mask;
                ++sz;
                return;
            }
            mask ^= basis[i];
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N;
    cin >> N;
    vector<pair<ll,ll>> cost((1 << N) - 1);
    for (int i = 0; i < (1 << N) - 1; i++) {
        cin >> cost[i].first;
        cost[i].second = i + 1;
    }
    sort(cost.begin(), cost.end());
    Solver s;
    ll tot = 0;
    for (int i = 0; i < cost.size(); i++) {
        Solver st = s;
        st.insertVector(cost[i].second);
        if (st.sz == s.sz) {
            continue;
        }
        s = st;
        tot += cost[i].first;
    }
    cout << tot << '\n';
}
