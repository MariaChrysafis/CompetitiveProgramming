#include <vector>
#include <iostream>
#include <cassert>
#include <cmath>
#include <set>
#include <map>
#include <stack>
#include <set>
#define ll long long
using namespace std;
const int MOD = 2019201997;
int main() {
    freopen("walk.in", "r", stdin);
    freopen("walk.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N, K;
    cin >> N >> K;
    cout << MOD - (48 * N + 84 * (K - 1));
}
