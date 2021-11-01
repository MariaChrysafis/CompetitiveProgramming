#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_set>
#include <set>
#include <unordered_map>
#include <queue>
#include <map>
#define ll signed long long
using namespace std;
int main() {
	int n, m;
	cin >> n >> m;
	vector<int> a(n), b(m);
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	for (int i = 0; i < m; i++) {
		cin >> b[i];
	}
	vector<int> dp[1001];
	for (int i = 0; i < (1 << m); i++) {
		ll sum = 0;
		for (int j = 0; j < m; j++) {
			if (i & (1 << j)) {
				sum += b[j];
			}
		}
		if (sum <= 1000) {
			dp[sum].push_back(i);
		}
	}
	int prev[(1 << m)];
	int cur[(1 << m)];
	for (int j = 0; j < (1 << m); j++) {
		prev[j] = cur[j] = false;
	}
	for (int i: dp[a[0]]) {
		prev[i]++;
	}
	for (int i = 1; i < n; i++) {
		for (int j = 0; j < (1 << m); j++) {
			if (!prev[j]) {
				continue;
			}
			for (int val: dp[a[i]]) {
				if ((val & j) == 0) {
					cur[val + j] += prev[j];
				}
			}
		}
		for (int j = 0; j < (1 << m); j++) {
			prev[j] = cur[j];
			cur[j] = false;
		}
	}
	bool bo = false;
	for (int i = 0; i < (1 << m); i++) {
		bo = bo || prev[i];
	}
	if (bo) {
		cout << "YES";
	} else {
		cout << "NO";
	}
}
