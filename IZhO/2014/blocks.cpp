#include <vector>
#include <iostream>
#include <cassert>
#include <cmath>
#include <map>
#include <set>
#include <stack>
using namespace std;
const int64_t INF = 1e17;
struct Stack {
	vector<pair<int64_t, int64_t>> st; //[value, previous min]
	int64_t mn;
	Stack() {
		this->mn = INF;
	}
	void add(int64_t x) {
		st.push_back(make_pair(x, mn));
		mn = min(mn, x);
	}
	void pop() {
		mn = st.back().second;
		st.pop_back();
	}
};
int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N, K;
    cin >> N >> K;
    int64_t arr[N];
    for (int i = 0; i < N; i++) {
        cin >> arr[i];
    }
    vector<int64_t> prev(N + 1), cur(N + 1);
    prev.assign(N + 1, INF), cur.assign(N + 1, INF);
    for (int j = 1; j <= N; j++) {
        prev[j] = ((j == 1) ? arr[0] : max(prev[j - 1], arr[j - 1]));
    }
    for (int i = 2; i <= K; i++) {
    	vector<pair<pair<int64_t,int64_t>,pair<int64_t,int64_t>>> ranges;
    	Stack st;
        for (int j = 1; j <= N; j++) {
        	cur[j] = INF;
            if (j == 1) {
            	cur[1] = prev[0] + arr[0];
            	st.add(arr[0] + prev[0]);
            	ranges.push_back(make_pair(make_pair(arr[0], prev[0]), make_pair(0, 0)));
            } else {
            	int64_t mn = prev[j - 1];
            	while (!ranges.empty() and ranges.back().first.first <= arr[j - 1]) {
            		mn = min(mn, ranges.back().first.second);
            		ranges.pop_back();
            		st.pop();
            	}
            	if (ranges.empty()) {
            		ranges.push_back(make_pair(make_pair(arr[j - 1], mn), make_pair(0, j - 1)));
            		st.add(arr[j - 1] + mn);
            	} else {
            		ranges.push_back(make_pair(make_pair(arr[j - 1], mn), make_pair(ranges.back().second.second + 1, j - 1)));
            		st.add(arr[j - 1] + mn);
            	}
                cur[j] = st.mn;
            }
        }
        swap(cur, prev);
    }
    cout << prev[N];
}
