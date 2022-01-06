#include <iostream>
#include <vector>
#include <chrono>
#include <cstdint>
#include <algorithm>
#include <string>
#include <set>
#include <cmath>
#include <queue>
#include <deque>
#include <cassert>
#include <fstream>
#include <map>
#include <iomanip>
#include <sstream>

using namespace std;
typedef long long ll;
const ll MAX = 1e18;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll N, X;
    cin >> N >> X;
    map<ll,ll> prev;
    prev[1] = 1;
    for (int i = 0; i < N; i++) {
        int L;
        cin >> L;
        map<ll,ll> cur;
        for (int j = 0; j < L; j++) {
            ll x;
            cin >> x;
            for (auto& p: prev) {
                if (p.first <= X/x) {
                    cur[p.first * x] += p.second;
                }
            }
        }
        prev = cur;
    }
    cout << prev[X] << '\n';
}
