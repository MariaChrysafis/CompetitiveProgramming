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
#include <bitset>
#include <string>
#include <queue>
#include <string>
#include <map>
#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")
#pragma GCC optimization ("Ofast")
using namespace std;
void rotate (vector<string>& arr) {
    int N = arr.size();
    for (int x = 0; x < arr.size()/2; x++) {
        for (int y = x; y < N - x - 1; y++) {
            char temp = arr[x][y];
            arr[x][y] = arr[y][N - 1 - x];
            arr[y][N - 1 - x] = arr[N - 1 - x][N - 1 - y];
            arr[N - 1 - x][N - 1 - y]= arr[N - 1 - y][x];
            arr[N - 1 - y][x] = temp;
        }
    }
}
int solve (vector<string>& arr) {
    vector<bitset<300>> vec(arr.size());
    for (int i = 0; i < arr.size(); i++) {
        for (int j = 0; j < arr.size(); j++) {
            vec[i].set(j, (arr[i][j] == '*'));
        }
    }
    int ans = 0;
    for (int x1 = 0; x1 <= arr.size(); x1++) {
        for (int y1 = x1 + 1; y1 <= arr.size(); y1++) {
            for (int b = 0; b < arr.size(); b++) {
                if (b + x1 + y1 >= arr.size()) continue;
                //[b, a]
                //[b + x1 , a + 2y_1 - x_1]
                //[b + x_1 + y_1, y_1 - x_1 + a]
                ans += (vec[b] & (vec[b + x1] >> (2 * y1 - x1)) & (vec[b + x1 + y1]) >> (y1 - x1)).count();
            }
        }
    }
    return ans;
}
int main () {
    freopen("triangles.in", "r", stdin);
    freopen("triangles.out", "w", stdout);
    int n;
    cin >> n;
    vector<string> arr;
    arr.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    int t = 4;
    int ans = 0;
    while (t--) {
        ans += solve(arr);
        rotate(arr);
    }
    cout << ans;
}
