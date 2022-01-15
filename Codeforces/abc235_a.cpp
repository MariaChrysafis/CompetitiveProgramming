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

#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")

using namespace std;

typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string s;
    cin >> s;
    int ans = (s[0] - '0') + (s[1] - '0') + (s[2] - '0');
    cout << ans * 111;
}
