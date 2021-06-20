#include <iostream>
#include <algorithm>
using namespace std;
const long long INF = 1000000000000000000;
int main(){
    int n, q;
    cin >> n >> q;
    long long arr[n];
    long long sum = 0;
    for(int i = 0; i < n; i++){
        cin >> arr[i];
        sum += arr[i];
    }
    if(n < 3){
        cout << sum/100 * (100 - q) << endl;
        return 0;
    }
    sort(arr, arr + n);
    long long dp[n];
    dp[0] = arr[0]/100 * (100 - q);
    dp[1] = (arr[0] + arr[1])/100 * (100 - q);
    dp[2] = (arr[0] + arr[1] + arr[2])/100 * (100 - q);
    dp[2] = min(dp[2], arr[1] + arr[2]);
    for(int i = 3; i < n; i++){
        dp[i] = INF;
        dp[i] = min(dp[i], dp[i - 3] + arr[i] + arr[i - 1]);
        dp[i] = min(dp[i], dp[i - 2] + (arr[i] + arr[i - 1])/100 * (100 - q));
        dp[i] = min(dp[i], dp[i - 1] + arr[i]/100 * (100 - q));
    }
    cout << dp[n - 1] << endl;
}
