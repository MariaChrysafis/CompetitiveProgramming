#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <cmath>
using namespace std;
vector<int> arr;
const int INF = 1e9;
int main(){
    int n;
    cin >> n;
    arr.resize(n);
    for(int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    int dp[n][n][2];
    if(n == 1){
        cout << 0 << endl;
        return 0;
    }
    for(int pref = 0; pref < n; pref++){
        for(int hills = 0; hills < n; hills++){
            for(int last = 0; last < 2; last++){
                if(pref == 0) {
                    if (last == hills) dp[pref][hills][last] = 0;
                    else dp[pref][hills][last] = INF;
                    continue;
                }
                if(hills == 0) {
                    if(!last) dp[pref][hills][last] = 0;
                    else dp[pref][hills][last] = INF;
                    continue;
                }
                int ans = 0;
                if(!last){
                    ans = min(dp[pref - 1][hills][1] + max(arr[pref] - arr[pref - 1] + 1, 0), dp[pref - 1][hills][0]);
                }else{
                    int op1 = dp[pref - 1][hills - 1][0] + max(arr[pref - 1] - arr[pref] + 1, 0);
                    int op2 = INF;
                    if(pref - 2 >= 0){
                        op2 = dp[pref - 2][hills - 1][1] + max(0, arr[pref - 1] - min(arr[pref - 2], arr[pref]) + 1);
                    }
                    ans = min(op1, op2);
                }
                dp[pref][hills][last] = ans;
            }
        }
    }
    for(int i = 1; i <= (n + 1)/2; i++){
        cout << min(dp[n - 1][i][0], dp[n - 1][i][1]) << " ";
    }
 
}
