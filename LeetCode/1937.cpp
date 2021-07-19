class Solution {
public:
    vector<vector<int>> arr;
    vector<vector<long long>> dp;
    vector<long long> pref, suf;
    const long long INF = 1e9;
    long long memoize (int x, int y){
        if(dp[x][y] != -INF){
            return dp[x][y];
        }
        if(x == 0){
            dp[x][y] = arr[x][y];
            return dp[x][y];
        }
        long long myMax = 0;
        for(int k = 0; k < arr[0].size(); k++){
            //(x, i)
            long long pos = memoize(x - 1, k) + arr[x][y] - abs(k - y);
            myMax = max(myMax, pos);
        }
        dp[x][y] = myMax;
        return myMax;
    }
    long long maxPoints(vector<vector<int>>& points) {
        arr = points;
        dp.resize(points.size());
        pref.resize(points[0].size());
        suf.resize(points[0].size());
        for(int i = 0; i < points.size(); i++){
            dp[i].resize(points[0].size());
            for(int j = 0; j < points[0].size(); j++){
                dp[i][j] = -INF;
                if(i == 0){
                    dp[i][j] = arr[i][j];
                }
            }
        }
        pref = dp[0];
        for(int i = 0; i < dp[0].size(); i++){
            if(i != 0) pref[i] = max(pref[i - 1], dp[0][i] + i);
            else pref[i] = dp[0][i] + i;
        }
        for(int i = dp[0].size() - 1; i >= 0; i--){
            if(i != dp[0].size() - 1) suf[i] = max(suf[i + 1], dp[0][i] - i);
            else suf[i] = dp[0][i] - i;
        }
        for(int i = 1; i < points.size(); i++){
            for(int j = 0; j < points[0].size(); j++){
                long long myMax = suf[j] + arr[i][j] + j;
                /*
                for(int k = j; k < points[0].size(); k++){
                    long long pos = dp[i - 1][k] - k + j + arr[i][j];
                    myMax = max(myMax, pos);
                }
                */
                myMax = max(myMax, pref[j] + arr[i][j] - j);
                dp[i][j] = myMax;
            }
            for(int j = 0; j < dp[0].size(); j++){
                if(j != 0) pref[j] = max(pref[j - 1], dp[i][j] + j);
                else pref[j] = dp[i][j] + j;
            }
            for(int j = dp[0].size() - 1; j >= 0; j--){
                if(j != dp[0].size() - 1) suf[j] = max(suf[j + 1], dp[i][j] - j);
                else suf[j] = dp[i][j] - j;
            }
        }
        long long ans = 0;
        //for(int i = 0; i < points.size(); i++){
            for(int j = 0; j < points[0].size(); j++){
                ans = max(dp[points.size() - 1][j], ans);
            }
            //cout << endl;
        //}
        return ans;
    }
};
