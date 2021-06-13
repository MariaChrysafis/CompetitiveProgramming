#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <array>
#include <stack>
#include <map>
using namespace std;
void print(vector<vector<char>> v){
    cout << "YES" << endl;
    for(int i = 0; i < v.size(); i++){
        for(int j = 0; j < v[0].size(); j++){
            cout << v[i][j];
        }
        cout << endl;
    }
}
bool valid(vector<vector<char>> arr, char c1, char c2){
    for(int i = 0; i < arr.size(); i++){
        for(int j = 0; j < arr[0].size(); j++){
            if((i + j) % 2 == 0){
                if(arr[i][j] == c1) return false;
                arr[i][j] = c2;
            }else{
                if(arr[i][j] == c2) return false;
                arr[i][j] = c1;
            }
        }
    }
    return true;
}
vector<vector<char>> color(vector<vector<char>> arr, char c1, char c2){
    for(int i = 0; i < arr.size(); i++){
        for(int j = 0; j < arr[0].size(); j++){
            if((i + j) % 2 == 0){
                arr[i][j] = c2;
            }else{
                arr[i][j] = c1;
            }
        }
    }
    return arr;
}
void solve(){
    int n, m;
    cin >> n >> m;
    vector<vector<char>> arr;
    arr.resize(n);
    for(int i = 0; i < n; i++){
        arr[i].resize(m);
        for(int j = 0; j < m; j++){
            cin >> arr[i][j];
        }
    }
    vector<char> pos = {'R', 'W'};
    for(char c1: pos){
        for(char c2: pos) {
            if(c1 == c2) continue;
            if (valid(arr, c1, c2)) {
                print(color(arr, c1, c2));
                return;
            }
        }
    }
    cout << "NO" << endl;
}
int main(){
    int t;
    cin >> t;
    while(t--){
        solve();
    }
}
