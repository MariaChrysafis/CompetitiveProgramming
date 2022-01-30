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
bool valid (vector<int> v) {
	int ans = 0;
	int sm = 0;
	for (int i = 0; i < v.size(); i++) {
		ans = v[i] - ans;
		sm += v[i];
		if (ans < 0) {
			return false;
		}
	}
	return (ans == 0);
}
bool valid1 (vector<int> v) {
	int A = 0;
	for (int i = 0; i < v.size(); i++) {
		A = v[i] - A;
	}
	if (A < 0) {
		return false;
	}
	int ans = 0;
	for (int i = 0; i < v.size(); i++) {
		ans = v[i] - ans;
		if (i % 2 == 0) {
			if (A - ans > 0) {
				return false;
			}
		} else {
			if (ans < 0) {
				return false;
			}
		}
	}
	return true;
}
int cntr = 0;
void construct (vector<int> base, vector<int> v) {
	if (v.size() == base.size()) {
		if (valid(v) && base.size() % 2 == 0) {
			/*
			for (int i: v) {
				cout << i << ' ';
			}
			cout << '\n';
			*/
			cntr++;
		}
		if (valid1(v) && base.size() % 2 == 1) {
			/*
			for (int i: v) {
				cout << i << ' ';
			}
			cout << '\n';
			*/
			cntr++;
		}
		return;
	} 
	for (int i = 0; i <= base[v.size()]; i++) {
		vector<int> v1 = v; v1.push_back(i);
		construct(base, v1);
	}
}
int main() {
	int n;
	cin >> n;
	vector<int> v(n);
	for (int i = 0; i < n; i++) {
		cin >> v[i];
	}
	construct(v, {});
	cout << cntr;
}
