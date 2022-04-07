#include <cmath>
#include <iostream>
#include <set>
#include <climits>
#include <cstdio>
#include <algorithm>
#include <cassert>
#include <string>
#include <vector>
#include <iomanip>
#include <unordered_map>
#include <type_traits>
#include <string>
#include <queue>
#include <map>

using namespace std;
class Node {
public:
	int dp[4];
	Node () {
		dp[0] = dp[1] = dp[2] = dp[3] = 3;
		dp[0] = 0;
	}
	Node (pair<int,int> p1, pair<int,int> p2) {
		dp[0] = 0;
		dp[1] = 1 * (p1.first <= p2.first) + 2 * (p1.first <= p2.second);
		dp[2] = 1 * (p1.second <= p2.first) + 2 * (p1.second <= p2.second);
		dp[3] = dp[1] | dp[2];
	}
};
Node merge (Node x, Node y) {
	Node ans;
	for (int i = 0; i < 4; i++) {
		ans.dp[i] = y.dp[x.dp[i]];
	}
	return ans;
}
template<class T>
class SegmentTree {
public:

	SegmentTree (int N) {
		N = (1 << ((int)floor(log2(N - 1)) + 1));
		this->N = N;
		val.assign(2 * N, ID);
	}

	void update (int x, T y) {
		x += N - 1;
		val[x] = y;
		while (x != 0) {
			x = (x - 1)/2;
			val[x] = merge(val[2 * x + 1], val[2 * x + 2]);
		}
	}

	T query (int ind, const int l, const int r, int tl, int tr) {
		if (tl >= l && tr <= r) {
			return val[ind];
		}
		if (tr < l || tl > r) {
			return ID;
		}
		return merge(query(2 * ind + 1, l, r, tl, (tl + tr)/2), query(2 * ind + 2, l, r, (tl + tr)/2 + 1, tr));
	}

	T query (int l, int r) {
		return query(0, l, r, 0, N - 1);
	}
private:
	vector<T> val;
	T ID;
	int N;
};
int main () {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int N;
	cin >> N;
	vector<pair<int,int>> vec(N + 2);
	vec[0] = {0, 0};
	for (int i = 1; i <= N; i++) {
		cin >> vec[i].first >> vec[i].second;
	}
	vec.back() = {(int)1e9, (int)1e9};
	SegmentTree<Node> st(N + 1);
	for (int i = 0; i < vec.size() - 1; i++) {
		st.update(i, Node(vec[i], vec[i + 1]));
	}
	int Q;
	cin >> Q;
	while (Q--) {
		int x, y;
		cin >> x >> y;
		swap(vec[x], vec[y]);
		st.update(x, Node(vec[x], vec[x + 1]));
		st.update(x - 1, Node(vec[x - 1], vec[x]));
		st.update(y, Node(vec[y], vec[y + 1]));
		st.update(y - 1, Node(vec[y - 1], vec[y]));
		if (st.query(0, N).dp[3] == 0) {
			cout << "NIE\n";
		} else {
			cout << "TAK\n";
		}
	}

}
