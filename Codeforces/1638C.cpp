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
    	vector<int> a(n);
    	vector<bool> marked;
    	marked.assign(n + 1, false);
    	for (int i = 0; i < n; i++) {
    		cin >> a[i];
    	}
    	int soFar = 0; //we've achieved everything from 1...soFar
    	int cntr = 0;
    	int myMax = 0;
    	for (int i = 0; i < n - 1; i++) {
    		marked[a[i]] = true;
    		myMax = max(myMax, a[i]);
    		bool vis = false;
    		while (marked[soFar + 1]) {
    			soFar++;
    			vis = true;
    		}
    		if (vis == true && myMax == soFar) {
    			cntr++;
    		}
    	}
    	cout << cntr + 1 << '\n';
    }
}
