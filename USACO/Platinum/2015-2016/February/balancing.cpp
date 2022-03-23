#include <vector>
#include <algorithm>
#include <iostream>
#include <set>
#include <cmath>
#include <map>
#include <random>
#include <cassert>
#include <ctime>
#include <cstdlib>
#include <limits.h>

using namespace std;

int MAXX = (int)200000 + 10;
int MAXY = (int)200000 + 10;
template<class T> struct Seg { // comb(ID,b) = b
	const T ID = 0; T comb(T a, T b) { return a+b; }
	int n; vector<T> seg;
	void init(int _n) { n = _n; seg.assign(2*n,ID); }
	void pull(int p) { seg[p] = comb(seg[2*p],seg[2*p+1]); }
	void upd(int p, T val) { // set val at position p
		seg[p += n] += val; for (p /= 2; p; p /= 2) pull(p); }
	T query(int l, int r) {	// sum on interval [l, r]
		T ra = ID, rb = ID;
		for (l += n, r += n+1; l < r; l /= 2, r /= 2) {
			if (l&1) ra = comb(ra,seg[l++]);
			if (r&1) rb = comb(seg[--r],rb);
		}
		return comb(ra,rb);
	}
};
void compress (vector<pair<int,int>> &vec) {
	set<int> x, y;
	for (auto& p: vec) x.insert(p.first), y.insert(p.second);
	map<int,int> myMap1, myMap2;
	int cnt = 1;
	for (int x1: x) {
		myMap1[x1] = (cnt += 2);
	}
	cnt = 1;
	for (int y1: y) {
		myMap2[y1] = (cnt += 2);
	}
	for (int i = 0; i < vec.size(); i++) {
		vec[i].first = myMap1[vec[i].first];
		vec[i].second = myMap2[vec[i].second];
	}
}
int solver (vector<pair<int,int>> vec, int N) {
	compress(vec);
	vector<vector<int>> coord1(MAXY);
	vector<vector<int>> coord2(MAXX);
	for (int i = 0; i < N; i++) {
		coord1[vec[i].second].push_back(vec[i].first);
		coord2[vec[i].first].push_back(vec[i].second);
	}
	Seg<int> stL; stL.init(MAXY + 1);
	Seg<int> stR; stR.init(MAXY + 1);
	for (int i = 0; i < MAXY; i++) {
		stR.upd(i, coord1[i].size());
	}
	int myMin = INT_MAX;
	bool prev = true;
	for (int x = 0; x < MAXX; x++) {
		if (x % 2 == 1) {
			prev = false;
			for (int y: coord2[x]) {
				stL.upd(y, 1);
				stR.upd(y, -1);
				prev = true;
			}
			continue;
		}
		if (!prev) {
			continue;
		}
		int totL = stL.query(0, MAXY - 1);
		int totR = stR.query(0, MAXY - 1);
		int l = 0;
		int r = MAXY - 2;
		for (int dum = 0; dum <= 1; dum++) {
			l = 0, r = MAXY - 2;
			while (l != r) {
				int m = (l + r) / 2;
				if (stL.query(0, m) >= totL / 2 + dum) {
					r = m;
				} else {
					l = m + 1;
				}
			}
			int y = l;
			int lower_left = stL.query(0, y);
			int lower_right = stR.query(0, y);
			myMin = min(myMin, max(max(lower_right, totR - lower_right), max(lower_left, totL - lower_left)));
		}
	}
	return myMin;
}
int main() {
	freopen("balancing.in", "r", stdin);
	freopen("balancing.out", "w", stdout);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int N;
	cin >> N;
	vector<pair<int,int>> vec(N);
	for (int i = 0; i < N; i++) {
		cin >> vec[i].first >> vec[i].second;
	}
	int ans = solver(vec, N);
	for (int i = 0; i < N; i++) {
		vec[i].first = MAXX - vec[i].first;
	}
	ans = min(ans, solver(vec, N));
	cout << ans << '\n';

}
