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
bool comp (pair<int,int> p1, pair<int,int> p2) {
	return (p1.second < p2.second);
}
int main () {
	int N;
	cin >> N;
	vector<int> arr(N);
	vector<int> pref(N + 1);
	pref[0] = 0;
	for (int i = 0; i < N; i++) {
		cin >> arr[i];
		pref[i + 1] = pref[i] + arr[i];
	}
	map<int,vector<pair<int,int>>> intervals;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j <= i; j++) {
			intervals[pref[i + 1] - pref[j]].emplace_back(j, i);
		}
	}
	vector<pair<int,int>> ans;
	for (auto& p: intervals) {
		sort(p.second.begin(), p.second.end(), comp);
		vector<pair<int,int>> res;
		int overlap = p.second[0].second;
		res = {p.second[0]};
		for (int i = 1; i < p.second.size(); i++) {
			if (p.second[i].first > overlap) {
				overlap = p.second[i].second;
				res.emplace_back(p.second[i]);
			}
		}
		if (res.size() > ans.size()) {
			ans = res;
		}
	}
	cout << ans.size() << '\n';
	for (auto& p: ans) {
		cout << p.first + 1 << " " << p.second + 1 << '\n';
	}
}
