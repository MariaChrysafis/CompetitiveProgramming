#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <map>
using namespace std;
const int INF = 1e9;
int solver(vector<char> v){
    int cntr = 0;
    for(int i = 0; i < v.size(); i++){
        if(v[i] == 'O') return INF;
        if(v[i] == '.') cntr++;
    }
    return cntr;
}
vector<vector<char>> transpose(vector<vector<char>> vec){
    for(int i = 0; i < vec.size(); i++){
        for(int j = i + 1; j < vec.size(); j++){
            swap(vec[i][j], vec[j][i]);
        }
    }
    return vec;
}
vector<int> helper(vector<vector<char>> v){
    vector<int> ans;
    for(int i = 0; i < v.size(); i++){
        ans.push_back(solver(v[i]));
    }
    return ans;
}
bool valid(vector<vector<char>> v, int x, int y){
    bool row = true;
    bool col = true;
    for(int i = 0; i < v.size(); i++){
        for(int j = 0; j < v[0].size(); j++){
            if(i == x && v[i][j] != 'X') row = false;
            if(j == y && v[i][j] != 'X') col = false;
        }
    }
    return (row || col);
}
void solve(){
    int n;
    cin >> n;
    vector<vector<char>> v(n);
    for(int i = 0; i < n; i++){
        string s;
        cin >> s;
        v[i].resize(n);
        for(int j = 0; j < n; j++){
            v[i][j] = s[j];
        }
    }
    vector<int> v1 = helper(transpose(v));
    vector<int> v2 = helper(v);
    sort(v1.begin(), v1.end());
    sort(v2.begin(), v2.end());
    int myMin = min(v1[0], v2[0]);
    int cntr = 0;
    for(int i: v1){
        cntr += (myMin == i);
    }
    for(int i: v2){
        cntr += (myMin == i);
    }
    if(myMin != 1) {
        if(myMin == INF) {
            cout << "Impossible";
            return;
        }
        cout << myMin << " " << cntr;
    }else {
        cntr = 0;
        for(int i = 0; i < v.size(); i++){
            for(int j = 0; j < v[0].size(); j++){
                if(v[i][j] == '.') {
                    v[i][j] = 'X';
                    if (valid(v, i, j)) {
                        cntr++;
                    }
                    v[i][j] = '.';
                }
            }
        }
        cout << myMin << " " << cntr;
    }
}
int main(){
    int t;
    cin >> t;
    for(int i = 0; i < t; i++){
        cout << "Case #" << i + 1 << ": ";
        solve();
        if(i != t - 1){
            cout << "\n";
        }
    }
}
