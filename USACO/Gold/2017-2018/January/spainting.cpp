#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <cmath>
#include <iomanip>
using namespace std;
const long long MOD = 1e9 + 7;
int main() {
	freopen("spainting.in", "r", stdin);
	freopen("spainting.out", "w", stdout);
	int N, M, K;
	cin >> N >> M >> K;
	long long dp[N + 1];
	dp[0] = 1;
	for (int i = 1; i < K; i++) {
		dp[i] = dp[i - 1] * M;
		dp[i] %= MOD;
	}
	dp[K] = dp[K - 1] * M - M;
	dp[K] %= MOD;
	for (int i = K + 1; i <= N; i++) {
		dp[i] = (M * dp[i - 1] - (M - 1) * dp[i - K] + M * MOD) % MOD;
	}
	long long powr = 1;
	for (int i = 0; i < N; i++) {
		powr *= M;
		powr %= MOD;
	}
	cout << (powr - dp[N] + MOD) % MOD << endl;
}
