#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <set>
#include <map>
 
using namespace std;
 
string yesNo(bool b){
    if(b) return "Yes";
    else return "No";
}
 
void print(vector<int> v) {
    for (int i: v) cout << i << ' ';
    cout << endl;
}
 
int to_int(char c){
 
}
 
int n, m;
 
bool inBounds(int x, int y){
    return (x < n && y < m && x >= 0 && y >= 0);
}
 
void solve(){
    cin >> n >> m;
    char arr[n][m];
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            arr[i][j] = '0';
        }
    }
    vector<pair<int,int>> direction;
    direction.push_back({-1, 1});
    direction.push_back({1, -1});
    direction.push_back({1, 1});
    direction.push_back({-1, -1});
    direction.push_back({0, -1});
    direction.push_back({0, 1});
    direction.push_back({-1, 0});
    direction.push_back({1, 0});
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            bool valid = true;
            for(pair<int,int> dir: direction){
                pair<int,int> pos = {dir.first + i, dir.second + j};
                if(inBounds(pos.first, pos.second) && arr[pos.first][pos.second] == '1'){
                    valid = false;
                }
            }
            if(valid && (i == 0 || j == 0 || i == n - 1 || j == m - 1)){
                arr[i][j] = '1';
            }
        }
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            cout << arr[i][j];
        }
        cout << '\n';
    }
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}
 
/*
 * Notes to self:
 * before implementing THINK
 * Long Long vs Int?
 */
