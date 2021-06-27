#include <iostream>
#include <vector>
using namespace std;
struct solver{
    int n, m, k;
    vector<pair<int,int>> v;
    vector<vector<int>> grid;
    vector<vector<int>> pref;
    bool valid(){
        for(int i = 1; i <= n - k; i++){
            for(int j = 1; j <= m - k; j++){
                if(abs(pref[i + k][j + k] - pref[i + k][j - 1] - pref[i - 1][j + k] + pref[i - 1][j - 1]) == (k + 1) * (k + 1)){
                    return true;
                }
            }
        }
        return false;
    }
    void main(){
        cin >> n >> m >> k;
        k--;
        v.resize(n * m);
        grid.resize(n + 1), pref.resize(n + 1);
        for(int i = 0; i <= n; i++){
            grid[i].resize(m + 1), pref[i].resize(m + 1);
            for(int j = 0; j <= m; j++){
                grid[i][j] = 0;
            }
        }
        vector<vector<int>> orig = grid;
        vector<pair<int,int>> vec(n * m);
        for(int i = 0; i < vec.size(); i++){
            int a, b;
            cin >> a >> b;
            vec[i] = make_pair(a,b);
        }
        int l = 0;
        int r = vec.size() - 1;
        while(l < r){
            int dum = (l + r)/2;
            grid = orig;
            for(int i = 0; i <= dum; i += 2) {
                grid[vec[i].first][vec[i].second] = 1;
            }
            for(int i = 1; i <= dum; i += 2){
                grid[vec[i].first][vec[i].second] = -1;
            }
            for(int x = 1; x <= n; x++){
                for(int y = 1; y <= m; y++){
                    pref[x][y] = pref[x - 1][y] + pref[x][y - 1] - pref[x - 1][y - 1] + grid[x][y];
                }
            }
            if(valid()){
                r = dum;
            }else{
                l = dum + 1;
            }
        }
        if(l == r){
            for(int i = 0; i <= l; i += 2) {
                grid[vec[i].first][vec[i].second] = 1;
            }
            for(int i = 1; i <= l; i += 2){
                grid[vec[i].first][vec[i].second] = -1;
            }
            for(int x = 1; x <= n; x++){
                for(int y = 1; y <= m; y++){
                    pref[x][y] = pref[x - 1][y] + pref[x][y - 1] - pref[x - 1][y - 1] + grid[x][y];
                }
            }
            if(valid()) {
                if(l % 2 == 0){
                    cout << "Alice\n";
                }else{
                    cout << "Bob\n";
                }
            }else{
                cout << "Draw\n";
            }
        }else{
            cout << "Draw\n";
        }
    }
};
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while(t--) {
        solver s;
        s.main();
    }
}
