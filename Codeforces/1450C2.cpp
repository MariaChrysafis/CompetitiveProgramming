#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <set>
#include <stack>
#include <map>
#define ll long long
using namespace std;
vector<bool> isPrime;
void print(vector<ll> v){
    for(int i: v) cout << i << " ";
    cout << endl;
}
char op(char c){
    if( c== 'X') return 'O';
    return 'X';
}
void print(vector<vector<char>> v){
    for(int i = 0; i < v.size(); i++){
        for(int j = 0; j < v[0].size(); j++)
            cout << v[i][j];
        cout << endl;
    }
}
pair<vector<vector<char>>, int> moves(vector<vector<char>> v, int x, int y){
    int cntr = 0;
    for(int i = 0; i < v.size(); i++){
        for(int j = 0; j < v.size(); j++){
            if(v[i][j] == '.') continue;
            if((i - j + v.size() * 3) % 3 == x){
                if(v[i][j] == 'O') cntr++, v[i][j] = 'X';
            }else if((i - j + v.size() * 3) % 3 == y){
                if(v[i][j] == 'X') cntr++, v[i][j] = 'O';
            }
        }
    }
    return {v,cntr};
}
 
void solve(){
    int n;
    cin >> n;
    vector<vector<char>> v(n);
    int cntr = 0;
    for(int i = 0; i < n; i++){
        v[i].resize(n);
        string s;
        cin >> s;
        for(int j = 0; j < n; j++){
            v[i][j] = s[j];
            cntr += (v[i][j] == 'O' || v[i][j] == 'X');
        }
    }
    vector<char> pos = {'X', 'O'};
    for(char c: pos) {
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                if(i == j) continue;
                if (moves(v, i, j).second <= cntr / 3) {
                    print(moves(v, i, j).first);
                    return;
                }
            }
        }
    }
 
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin >> t;
    while(t--){
        solve();
    }
 
}
