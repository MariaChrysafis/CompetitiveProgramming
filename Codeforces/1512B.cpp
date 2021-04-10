#include <iostream>
#include <map>
#include <vector>
using namespace std;
void solve(){
    int n;
    cin >> n;
    char arr[n][n];
    vector<pair<int,int>> v;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            char c;
            cin >> c;
            arr[i][j] = c;
            if(c == '*'){
                v.push_back({i, j});
            }
        }
    }
    pair<int,int> p1 = v[0];
    pair<int,int> p2 = v[1];
    if(p1.first != p2.first && p2.second != p1.second){
        arr[max(p1.first, p2.first)][min(p1.second, p2.second)] = '*';
        arr[min(p1.first, p2.first)][max(p1.second, p2.second)] = '*';
        arr[min(p1.first, p2.first)][min(p1.second, p2.second)] = '*';
        arr[max(p1.first, p2.first)][max(p1.second, p2.second)] = '*';
    }
    if(p1.first == p2.first){
        int x = 0;
        if(p1.first == 0) x = 1;
        arr[x][p1.second]= '*';
        arr[x][p2.second] = '*';
    }
    if(p1.second == p2.second){
        int x = 0;
        if(p1.second == 0) x++;
        arr[p1.first][x] = '*';
        arr[p2.first][x] = '*';
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cout << arr[i][j];
        }
        cout << endl;
    }
}
int main(){
    int t;
    cin >> t;
    while(t--){
        solve();
    }
}
