#include <vector>
#include <algorithm>
#include <iostream>
#include <set>
#include <cmath>
#include <map>
#include <random>
#include <cassert>
#include <ctime>
#include <bitset>
#include <stack>
#include <cstdlib>
#include <queue>
#include <stdint.h>
#include <vector>
#include <cassert>
#include <numeric>
#include <iostream>
#include <algorithm>
#include <functional>
#include <cstdio>
#include <limits.h>

using namespace std;

pair<int64_t,int64_t> merge (pair<int64_t,int64_t> p1, pair<int64_t,int64_t> p2) {
    if (p1.second > p2.first) return p1;
    if (p2.second > p1.first) return p2;
    return {max(p1.first, p2.first), min(p1.first, p2.first)};
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    cin >> T;
    while (T--) {
        int N;
        cin >> N;
        vector<int64_t> a(N), b(N);
        for (int i = 0; i < N; i++) {
            cin >> a[i];
        }
        for (int i = 0; i < N; i++) {
            cin >> b[i];
        }
        int64_t tot = 0;
        for (int i = 1; i < N; i++) {
            tot += min(a[i], b[i - 1]);
        }
        cout << tot << '\n';
    }

}
