#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <cmath>
#include <iomanip>
using namespace std;
vector<long long> milk;
vector<pair<long long,long long>> v;
vector<long long> rent;
vector<long long> gallon_pref = {0ll};
vector<long long> money_pref = {0ll};
bool comp(pair<int,int> p1, pair<int,int> p2) {
	return (p1.second > p2.second);
}
long long binSearch (long long x, int l, int r) {
	if (gallon_pref.back() <= x) {
		return money_pref.back();
	}
	int m = (l + r + 1)/2;
	if (gallon_pref[m] <= x && gallon_pref[m + 1] > x) {
		return money_pref[m] + abs(x - gallon_pref[m]) * v[m].second;
	}
	if (gallon_pref[m] <= x) {
		return binSearch(x, m + 1, r);
	} else {
		return binSearch(x, l, m - 1);
	}
}
int main() {
	freopen("rental.in", "r", stdin);
	freopen("rental.out", "w", stdout);
    long long N, M, R;
	cin >> N >> M >> R;
	milk.resize(N);
	for (int i = 0; i < N; i++) {
		cin >> milk[i];
	}
	v.resize(M);
	for (int i = 0; i < M; i++) {
		cin >> v[i].first >> v[i].second;
	}
	rent.resize(R);
	for (int i = 0; i < R; i++) {
		cin >> rent[i];
	}
	sort(milk.begin(), milk.end());
	sort(rent.begin(), rent.end());
	sort(v.begin(), v.end(), comp);
	reverse(milk.begin(), milk.end());
	reverse(rent.begin(), rent.end());
	vector<long long> rent_pref = {0};
	for (int i = 0; i < rent.size(); i++) rent_pref.push_back(rent_pref.back() + rent[i]);
	//for (auto p: v) cout << p.first << " " << p.second << endl;
	//cout << "---\n";
	for (int i = 0; i < v.size(); i++) {
		gallon_pref.push_back(v[i].first + gallon_pref.back());
		money_pref.push_back(v[i].first * v[i].second + money_pref.back());
	}
	long long milked = 0;
	long long myMax = 0;
	for (int i = 0; i <= N; i++) {
		myMax = max(myMax, rent_pref[min(N - i, R)] + binSearch(milked, 0, M));
		//cout << rent_pref[min(N - i, R)] << " " << binSearch(milked, 0, M) << endl;
		//if (i == 1) return 0;
		milked += milk[i];
	}
	cout << myMax << endl;
}
