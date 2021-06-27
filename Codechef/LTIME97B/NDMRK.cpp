#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
void print(vector<int> v){
    for(int i: v){
        cout << i << " ";
    }
    cout << endl;
}
struct tree{
    vector<vector<int>> children;
    vector<int> parent;
    int n, k;
    vector<vector<int>> dp;
    void init(){
        cin >> n >> k;
        parent.resize(n), children.resize(n);
        for(int i = 1; i < n; i++){
            cin >> parent[i];
            parent[i]--;
            children[parent[i]].push_back(i);
        }
    }
    int fill(int i){
        dp[i][0] = 0;
        int sz = 1;
        for(int j: children[i]){
            sz += fill(j);
            for(int l = min(k, sz); l >= 0; l--){
                for(int ind = 0; ind <= l; ind++){
                    dp[i][l] = min(dp[i][l], dp[j][ind] + dp[i][l - ind]);
                }
            }
        }
        if(sz <= k){
            dp[i][sz] = 1;
        }
        return sz;
    }
    void main(){
        init();
        const int INF = 100005;
        dp.resize(n);
        for(int i = 0; i < dp.size(); i++){
            dp[i].resize(k + 1);
            for(int j = 0; j < dp[0].size(); j++){
                dp[i][j] = INF;
            }
        }
        fill(0);
        for(int i = 0; i < k; i++){
            vector<int> o = dp[0];
            for(int j = k; j >= 0; j--){
                for(int l = 0; l <= j; l++){
                    dp[0][j] = min(dp[0][j], dp[0][l] + dp[0][j - l] + 1);
                }
            }
            if(o == dp[0]){
                break;
            }
        }
        cout << dp[0][k] << '\n';
    }
};

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin >> t;
    while(t--) {
        tree myTree;
        myTree.main();
    }
}
