#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <set>
#include <map>
 
using namespace std;
 
bool solve() {
    int n;
    cin >> n;
    vector<string> inp1(n);
    vector<string> inp2(n);
    for(int i = 0; i < n; i++){
        string s;
        cin >> s;
        inp1[i] = s;
    }
    for(int i = 0; i < n; i++){
        string s;
        cin >> s;
        inp2[i] = s;
    }
    vector<vector<bool>> ans(n);
    for(int i = 0; i < n; i++){
        ans[i].resize(n);
        for(int j = 0; j < n; j++){
            if(inp1[i][j] == inp2[i][j]){
                ans[i][j] = 0;
            }else{
                ans[i][j] = 1;
            }
        }
    }
    for(int i = 0; i < n; i++){
        if(ans[i][0] == 1){
            for(int j = 0; j < n; j++){
                ans[i][j] = !ans[i][j];
            }
        }
    }
    for(int i = 0; i < n; i++){
        int cntr = 0;
        for(int j = 0; j < n; j++){
            //cout << ans[i][j] << " ";
            cntr += ans[j][i];
        }
        if(cntr != 0 && cntr != n){
            return false;
        }
    }
    return true;
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while(t--) {
        bool b = solve();
        if(b) cout << "YES\n";
        else cout << "NO\n";
    }
}
