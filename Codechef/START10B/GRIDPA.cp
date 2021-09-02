#include <iostream>
#include <vector>
using namespace std;
struct solver{
    vector<vector<char>> vec;
    vector<vector<int>> gain;
    void read(){
        int n;
        cin >> n;
        int K;
        cin >> K;
        vec.resize(n), gain.resize(n);
        for(int i = 0; i < n; i++){
            vec[i].resize(n);
            string s;
            cin >> s;
            for(int j = 0; j < n; j++){
                vec[i][j] = s[j];
            }
        }
        for(int i = 0; i < n; i++){
            gain[i].resize(n);
            for(int j = 0; j < n; j++){
                cin >> gain[i][j];
            }
        }
        vector<vector<vector<int>>> dp(n);
        for(int i = 0; i < dp.size(); i++){
            dp[i].resize(n);
            for(int j = 0; j < dp[i].size(); j++){
                dp[i][j].resize(K + 1);
                for(int k = 0; k < dp[i][j].size(); k++){
                    dp[i][j][k] = -1e9;
                }
            }
        }
        int myMax = 0;
            dp[0][0][0] = gain[0][0];
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                if(vec[i][j] == '.'){
                    if(i != 0) dp[i][j][0] = max(dp[i][j][0], dp[i - 1][j][0] + gain[i][j]);
                    //if(i != n - 1) dp[i][j][0] = max(dp[i][j][0], dp[i + 1][j][0] + gain[i][j]);
                    if(j != 0) dp[i][j][0] = max(dp[i][j][0], dp[i][j - 1][0] + gain[i][j]);
                    //if(j != n - 1) dp[i][j][0] = max(dp[i][j][0], dp[i][j + 1][0] + gain[i][j]);
                }
                for(int k = 1; k <= K; k++){
                    //if(vec[i][j] == '#'){
                        if(i != 0) dp[i][j][k] = max(dp[i][j][k], dp[i - 1][j][k - 1] + gain[i][j]);
                        if(j != 0) dp[i][j][k] = max(dp[i][j][k], dp[i][j - 1][k - 1] + gain[i][j]);
                    //}
                }
                if(vec[i][j] == '.'){
                    if(i != 0) dp[i][j][K] = max(dp[i][j][K], dp[i - 1][j][K] + gain[i][j]);
                    //if(i != n - 1) dp[i][j][K] = max(dp[i][j][K], dp[i + 1][j][K] + gain[i][j]);
                    if(j != 0) dp[i][j][K] = max(dp[i][j][K], dp[i][j - 1][K] + gain[i][j]);
                    //if(j != n - 1) dp[i][j][K] = max(dp[i][j][K], dp[i][j + 1][K] + gain[i][j]);
                }
                //myMax = max(myMax, dp[i][j][K]);

            }
        }
        
        if(dp[n - 1][n - 1][K] > 0) cout << dp[n - 1][n - 1][K] << endl;
        else cout << -1 << endl;
    }
};
int main(){
    int t;
    cin >> t;
    while(t--){
        solver s;
        s.read();
    }
}
