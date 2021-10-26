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
using namespace std;
#define ll long long
struct cow {
    double weight;
    double talent;
};
double one = 1.0;
bool comp (cow c1, cow c2) {
    if (c1.weight == c2.weight) {
        //assert(false);
        return c1.talent > c2.talent;
    }
    return (c1.weight < c2.weight);
}
int main() {
    freopen("talent.in", "r", stdin);
    freopen("talent.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N, W;
    cin >> N >> W;
    vector<cow> vec;
    double myMax = 0;
    for (int i = 0; i < N; i++) {
        double x, y;
        cin >> x >> y;
        vec.push_back({x, y});
    }
    sort(vec.begin(), vec.end(), comp);
    double dp[N][W + 1];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j <= W; j++) {
            dp[i][j] = 0;
        }
    }
    dp[0][(int)vec[0].weight] = vec[0].talent;
    for (int i = 1; i < N; i++) {
        for (int j = 0; j <= W; j++) {
            dp[i][j] = dp[i - 1][j];
            if (j >= vec[i].weight) {
                dp[i][j] = max(dp[i][j], dp[i - 1][j - (int)vec[i].weight] + vec[i].talent);
            }
        }
    }
    myMax = max(myMax, (double)dp[N - 1][W]/(double)(W));
    for (int w = 0; w <= W; w++) {
        for (int i = 0; i < N; i++) {
            for (int j = i + 1; j < N; j++) {
                if (vec[j].weight + w < W) {
                    continue;
                }
                double weight = vec[j].weight + w;
                assert(weight >= W);
                double talent = vec[j].talent + dp[i][w];
                myMax = max(myMax, talent/weight);
                //cout << talent << " " << weight << " " << talent/weight << endl;
            }
        }
    }
    //cout << myMax << endl;
    cout << floor(myMax * 1000.0) << endl;
}
