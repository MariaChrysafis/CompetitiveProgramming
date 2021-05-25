#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
const int INF = 1e9;
vector<vector<int>> dp;
vector<vector<pair<int,int>>> backtrack;
string a, b;
int LCS(int la, int lb){
    //cout << la << " " << lb << endl;
    if(la == -1 || lb == -1){
        return 0;
    }
    if(dp[la][lb] != -1){
        return dp[la][lb];
    }
    if(a[la] == b[lb]){
        backtrack[la][lb] = {la - 1, lb - 1};
        dp[la][lb] = LCS(la - 1, lb - 1) + 1;
        return dp[la][lb];
    }
    int pos1 = LCS(la - 1, lb);
    int pos2 = LCS(la, lb - 1);
    if(pos1 > pos2){
        dp[la][lb] = pos1;
        backtrack[la][lb] = {la - 1, lb};
    }else{
        backtrack[la][lb] = {la, lb - 1};
        dp[la][lb] = pos2;
    }
    return dp[la][lb];
}
string ans;
void print(pair<int,int> p){
    //cout << p.first << " " << p.second << endl;
    if(p.first == -1 || p.second == -1) return;
    if(abs(backtrack[p.first][p.second].first - p.first) == abs(backtrack[p.first][p.second].second - p.second)){
        ans += a[p.first];
    }
    print({backtrack[p.first][p.second].first,backtrack[p.first][p.second].second});
}
int main(){
    cin >> a >> b;
    dp.resize(a.size() + 1);
    backtrack.resize(a.size() + 1);
    for(int i = 0; i <= a.size(); i++){
        dp[i].resize(b.size() + 1);
        backtrack[i].resize(b.size() + 1);
        for(int j = 0; j <= b.size(); j++){
            dp[i][j] = -1;
            backtrack[i][j] = {-1,-1};
        }
    }
    //return 0;
    int s = LCS(a.length() - 1, b.length() - 1);
    print({a.length() - 1, b.length() - 1});
    reverse(ans.begin(), ans.end());
    cout << ans << endl;
    //cout << s << endl;
}
