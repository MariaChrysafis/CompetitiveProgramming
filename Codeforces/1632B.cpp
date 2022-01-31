#include <cmath>
#include <cassert>
#include <iostream>
#include <set>
#include <climits>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <type_traits>
#include <string>
#include <queue>
#include <map>

using namespace std;
typedef int64_t ll;
int cost (vector<int> v) {
	int myMax = 0;
	for (int i = 0; i < v.size() - 1; i++) {
		myMax = max(myMax, v[i] ^ v[i + 1]);
	}
	return myMax;
}
void solve (int N) {
	int lg2 = log2(N - 1);
	int v = (1 << lg2);
	for (int i = v - 1; i >= 0; i--) {
		cout << i << ' ';
	}
	for (int i = v; i < N; i++) {
		cout << i << ' ';
	}
	cout << '\n';
}
int main() {
	int t;
	cin >> t;
	while (t--) {
		int N;
		cin >> N; 
		solve(N);
	}
}
