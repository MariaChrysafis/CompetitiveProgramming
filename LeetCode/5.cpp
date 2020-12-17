class Solution {
public:
    string longestPalindrome(string s) {
        bool dp[s.length()][s.length()];
        for(int i = 0; i < s.length(); i++){
            for(int j = 0; j < s.length(); j++){
                dp[i][j] = 0;
            }
        }
        for(int i = s.length() - 1; i >= 0; i--){
            for(int j = i; j < s.length(); j++){
                //cout << i << " " << j << endl;
                if(j == i){
                    dp[i][j] = 1;
                    continue;
                }
                if(j - 1 == i){
                    if(i + 1 != s.length() && s[i] == s[j]){
                        dp[i][j] = 1;
                        continue;
                    }
                }
                if(s[i] != s[j]){
                    dp[i][j] = 0;
                    continue;
                }
                if(i == s.length() - 1 || j == 0){
                    dp[i][j] = 0;
                    continue;
                }
                dp[i][j] = dp[i + 1][j - 1];
            }
        }
        string best = "";
        for(int i = 0; i < s.length(); i++){
            for(int j = 0; j < s.length(); j++){
                if(!dp[i][j]) continue;
                if(j - i + 1 > best.length()){
                    best = s.substr(i,j - i + 1);;
                }
            }
        }
        return best;
    }
};
