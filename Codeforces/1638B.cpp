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
#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("Ofast")
#pragma GCC optimization ("unroll-loops")

using namespace std;

bool sorted (vector<int> v) {
	vector<int> vec = v;
	sort(vec.begin(), vec.end());
	return (vec == v);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    for (int tc = 0; tc < t; tc++) {
    	int n;
    	cin >> n;
    	vector<vector<int>> a;
    	a.resize(2);
    	for (int i = 0; i < 2; i++) {
    		a[i].assign(n, 0);
    	}
    	for (int i = 0; i < n; i++) {
    		int x; cin >> x;
    		a[x % 2].push_back(x);
    	}
    	if (sorted(a[0]) && sorted(a[1])) {
    		cout << "YES\n";
    	} else {
    		cout << "NO\n";
    	}
    }
}
