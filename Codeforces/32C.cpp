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

ll rec (int N, int M, int S) {
    //map<int,int> oc;
    ll best = -1;
    ll cnt = 0;
    for (int i = 0; i < N; i++) {
        ll left = i;
        ll right = N - i - 1;
        if (left/S + right/S > best) {
            best = left/S + right/S;
            cnt = 1;
        } else if (left/S + right/S == best) {
            cnt++;
        }
    }
    return cnt;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll N, M, S;
    cin >> N >> M >> S;
    cout << rec(N, M, S) * rec(M, N, S);
}
