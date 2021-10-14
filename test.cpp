#include <vector>
#include <chrono>
#include <iostream>
#include <map>
#include <set>
#include <climits>
#include <cmath>
#include <cassert>
#include <algorithm>
//#pragma pack
using namespace std;
struct Point {
    long long x, y;
    long long manhattan() {
        return abs(x) + abs(y);
    }
};
struct Board {
    Point p1;
    Point p2;
	long long save() {
		return p2.manhattan() - p1.manhattan();
	}
};
bool abovePoint (Point p1, Point p2) {
	return (p1.x >= p2.x && p1.y >= p2.y);
}
bool above (Board b1, Board b2) {
	//is b1 above b2?
	return abovePoint(b1.p1, b2.p2);
}
bool comp(Board b1, Board b2) {
    return b1.p1.manhattan() < b2.p1.manhattan();
}
int main() {
    freopen("boards.in", "r", stdin);
    freopen("boards.out", "w", stdout);
    long long N, P;
    cin >> N >> P;
    vector<Board> vec(P);
    for (int i = 0; i < P; i++) {
        cin >> vec[i].p1.x >> vec[i].p1.y >> vec[i].p2.x >> vec[i].p2.y;
    }
    sort(vec.begin(), vec.end(), comp);
	long long dp[P];
	long long myMax = 0;
	for (int i = 0; i < P; i++) {
		dp[i] = vec[i].save();
		for (int j = 0; j < i; j++) {
			if (above(vec[i], vec[j])) {
				dp[i] = max(dp[i], dp[j] + vec[i].save());
			}
		}
		myMax = max(myMax, dp[i]);
		//cout << dp[i] << " ";
	}
	//cout << endl;
	//cout << myMax << endl;
	cout << 2 * N - myMax << endl;
}


