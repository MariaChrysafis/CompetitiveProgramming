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
void print(vector<vector<char>> v){
    for(int i = 0; i < v.size(); i++){
        for(int j = 0; j < v[0].size(); j++)
            cout << v[i][j];
        cout << endl;
    }
}
int moves(vector<vector<char>> v, int x){
    int cntr = 0;
    for(int i = 0; i < v.size(); i++){
        for(int j = 0; j < v.size(); j++){
            if(v[i][j] == '.') continue;
            if((i - j + v.size() * 3) % 3 == x){
                if(v[i][j] == 'X') cntr++;
            }else{
                if(v[i][j] == 'O') cntr++;
            }
        }
    }
    return cntr;
}
vector<vector<char>> change(vector<vector<char>> v, int x){
    for(int i = 0; i < v.size(); i++){
        for(int j = 0; j < v.size(); j++){
            if(v[i][j] == '.') continue;
            if((i - j + v.size() * 3) % 3 == x){
                if(v[i][j] == 'X') v[i][j] = 'O';
            }else{
                if(v[i][j] == 'O') v[i][j] = 'X';
            }
        }
    }
    return v;
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
            cntr += (v[i][j] == 'X');
        }
    }
    if(moves(v, 0) <= cntr/3){
        print(change(v, 0));
        return;
    }
    if(moves(v, 1) <= cntr/3){
        print(change(v, 1));
        return;
    }
    if(moves(v, 2) <= cntr/3){
        print(change(v, 2));
        return;
    }
    //cout << moves(v, 0) << " " << moves(v, 1) << " " << moves(v, 2) << endl;
 
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
