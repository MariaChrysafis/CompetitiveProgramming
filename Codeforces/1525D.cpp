#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <cmath>
#include <set>
 
using namespace std;
vector<int> arr;
vector<int> ones;
const long long INF = 1e13;
int main() {
    int n;
    cin >> n;
    arr.resize(n);
    long long dp[n + 1][n + 1];
    for(int i = 0; i < n; i++){
        cin >> arr[i];
        if(arr[i] == 1){
            ones.push_back(i);
        }
    }
    for(int i = 0; i <= n; i++){
        for(int j = 0; j <= n; j++){
            dp[i][j] = INF;
        }
        dp[i][0] = 0;
    }
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= ones.size(); j++){
            if(arr[i - 1] == 0){
                dp[i][j] = min(dp[i - 1][j], dp[i - 1][j - 1] + abs(ones[j - 1] - i + 1));
            }else{
                dp[i][j] = dp[i - 1][j];
            }
        }
    }
    cout << dp[n][ones.size()] << endl;
}
