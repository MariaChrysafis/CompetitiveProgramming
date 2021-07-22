#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <cmath>
using namespace std;
void print(vector<vector<int>> v){
    for(int i = 0; i < v.size(); i++){
        for(int j = 0; j < v[0].size(); j++){
            cout << v[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}
void print(vector<vector<long long>> v){
    for(int i = 0; i < v.size(); i++){
        for(int j = 0; j < v[0].size(); j++){
            cout << v[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}
void print(vector<vector<char>> v){
    for(int i = 0; i < v.size(); i++){
        for(int j = 0; j < v[0].size(); j++){
            cout << v[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}
void print(vector<int> v){
    for(int x: v) cout << x << " ";
    cout << endl;
}
void print(vector<long long> v){
    for(long long x: v) cout << x << " ";
    cout << endl;
}
void print(vector<char> v){
    for(char x: v) cout << x << " ";
    cout << endl;
}
int sumOfDigits(string s){
    int ans = 0;
    for(char c: s){
        ans += c - '0';
    }
    return ans;
}
void solve(){
    int x;
    cin >> x;
    cout << (x + 1)/10 << endl;
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while(t--){
        solve();
    }
}
