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

void myReverse (vector<int>& v, int l, int r) {
	for (int i = l; i <= l + (r - l)/2; i++) {
		swap(v[i], v[l + r - i]);
	}
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    for (int tc = 0; tc < t; tc++) {
    	int n;
    	cin >> n;
    	vector<int> p(n), oc(n);
    	for (int i = 0; i < n; i++) {
    		cin >> p[i]; 
    		p[i]--;
    		oc[p[i]] = i;
    	}
    	for (int i = 0; i < n; i++) {
    		if (oc[i] == i) {
    			continue;
    		}
    		myReverse(p, i, oc[i]);
    		break;
    	}
    	for (int i: p) {
    		cout << i + 1 << ' ';
    	}
    	cout << '\n';
    }
}
