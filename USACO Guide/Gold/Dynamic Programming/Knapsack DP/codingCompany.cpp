#include <cmath>
#include <iostream>
#include <set>
#include <climits>
#include <algorithm>
#include <cassert>
#include <vector>
#include <iomanip>
#include <type_traits>
#include <string>
#include <queue>
#include <map>

const int MOD = 1e9 + 7;
#define ll long long
#define MAX ((int)1e4 + 10)
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    long long N;
    cin >> N;
    long long X;
    cin >> X;
    vector<long long> arr(N);
    for (int i = 0; i < N; i++) {
        cin >> arr[i];
    }
    sort(arr.begin(), arr.end());
    long long prev[N + 1][MAX];
    long long cur[N + 1][MAX];
    for (int j = 0; j <= N; j++) {
        for (int k = 0; k < MAX; k++) {
            prev[j][k] = 0;
            cur[j][k] = 0;
        }
    }
    prev[0][MAX / 2] = 1; //no unfinished teams
    prev[1][MAX / 2 - arr[0]] = 1; //no finished teams
    for (int i = 1; i < N; i++) {
        for (int j = 0; j <= N; j++) {
            for (int k = 0; k < MAX; k++) {
                cur[j][k] = 0;
                cur[j][k] += prev[j][k]; //make a new empty team
                if (j != 0) cur[j][k] += prev[j][k] * j; //add to empty team
                if (j != 0) cur[j][k] += prev[j - 1][k + arr[i]]; //start a new team
                if (k - arr[i] >= 0 && j + 1 <= N) cur[j][k] += prev[j + 1][k - arr[i]] * (j + 1); //end a new team
                cur[j][k] %= MOD;
            }
        }
        for (int j = 0; j <= N; j++) {
            for (int k = 0; k < MAX; k++) {
                prev[j][k] = cur[j][k];
            }
        }
    }
    long long ans = 0;
    for (int j = 0; j <= MAX/2 + X; j++) {
        ans += prev[0][j];
        ans %= MOD;
    }
    cout << ans << endl;
}
