#include <iostream>
#include <vector>
using namespace std;
const int INF = 1e9;
struct day{
    vector<int> days;
};
int n;
vector<day> v;
vector<vector<int>> dp;
int main(){
    cin >> n;
    v.resize(n), dp.resize(n);
    for(int i = 0; i < n; i++) {
        dp[i].resize(3);
        int a, b, c;
        cin >> a >> b >> c;
        v[i] = {{a, b, c}};
        dp[i][0] = dp[i][1] = dp[i][2] = -INF;
    }
    dp[0][0] = v[0].days[0];
    dp[0][1] = v[0].days[1];
    dp[0][2] = v[0].days[2];
    for(int i = 1; i < n; i++){
        for(int j = 0; j < 3; j++){
            for(int k = 0; k < 3; k++){
                if(k == j) continue;
                dp[i][j] = max(dp[i][j], dp[i - 1][k] + v[i].days[j]);
            }
        }
    }
    cout << max(dp[n - 1][0], max(dp[n - 1][1], dp[n - 1][2])) << endl;
}
