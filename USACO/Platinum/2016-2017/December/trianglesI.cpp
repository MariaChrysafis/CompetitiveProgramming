#include <cmath>
#include <cassert>
#include <iostream>
#include <set>
#include <climits>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <bitset>
#include <type_traits>
#include <string>
#include <queue>
#include <map>

using namespace std;
class Point {
public:
    int64_t x, y;
    bool operator < (const Point& p1) const {
        return ((pair<int,int>){p1.x, p1.y} < (pair<int,int>){x, y});
    }
};
vector<Point> vec;
int main() {
    freopen("triangles.in", "r", stdin);
    freopen("triangles.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N;
    cin >> N;
    vec.resize(N);
    for (int i = 0; i < N; i++) {
        cin >> vec[i].x >> vec[i].y;
    }
    sort(vec.begin(), vec.end());
    int below[N][N];
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            below[i][j] = 0;
            for (int k = i + 1; k < j; k++) {
                vector<int64_t> v1 = {vec[k].x - vec[j].x, vec[k].y - vec[j].y};
                vector<int64_t> v2 = {vec[k].x - vec[i].x, vec[k].y - vec[i].y};
                int64_t cross = v1[0] * v2[1] - v1[1] * v2[0];
                if (cross > 0) {
                    below[i][j]++;
                }
            }
        }
    }
    vector<int> ans;
    ans.assign(N - 2, 0);
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            for (int k = j + 1; k < N; k++) {
                int x = below[i][k] - below[i][j] - below[j][k];
                if (x > 0) x--;
                x = abs(x);
                ans[x]++;
            }
        }
    }
    for (int i: ans) {
        cout << i << '\n';
    }
}
