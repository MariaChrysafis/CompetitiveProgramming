#include <iostream>
#define maxN 248

int dp[maxN][maxN];
int arr[maxN];
int N;

using namespace std;
int main(){
    freopen("248.in", "r", stdin);
    freopen("248.out", "w", stdout);
    cin >> N;
    for(int i = 0; i < N; i++){
        cin >> arr[i];
    }
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            dp[i][j] = -1;
        }
    }
    for(int l = 1; l <= N; l++){
        for(int i = 0; l + i - 1 < N; i++){
            int j = l + i - 1;
            dp[i][j] = -1;
            if(l == 1){ dp[i][j] = arr[i]; continue;}
            for(int k = 0; k < N; k++){
                if(dp[i][k] == -1) continue;
                if(dp[i][k] == dp[k + 1][j]){
                    dp[i][j] = max(dp[i][j],dp[i][k] + 1);
                }
            }
        }
    }
    int ans = 0;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            ans = max(ans,dp[i][j]);
        }
    }
    cout << ans << endl;
}
