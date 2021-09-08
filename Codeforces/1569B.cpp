#include <iostream>
#include <cmath>
#include <vector>
#include <chrono>
#include <map>
#define ll long long
using namespace std;
 
void solve(){
    int n;
    cin >> n;
    string s;
    cin >> s;
    vector<int> winner;
    vector<int> loser;
    for(int i = 0; i < s.length(); i++){
        if(s[i] == '1'){
            loser.push_back(i); // can never lose
        }else{
            winner.push_back(i); // can never win
        }
    }
    char arr[n][n];
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            arr[i][j] = '=';
            if(i == j){
                arr[i][j] = 'X';
            }
        }
    }
    for(int i = 0; i < winner.size(); i++){
        for(int j = i + 1; j < winner.size(); j++){
            if(i % 2 == j % 2) {
                arr[winner[i]][winner[j]] = '+';
                arr[winner[j]][winner[i]] = '-';
            }
            else {
                arr[winner[i]][winner[j]] = '-';
                arr[winner[j]][winner[i]] = '+';
            }
            //cout << winner[i] << " " << winner[j] << endl;
        }
    }
    for(int i = 0; i < n; i++){
        bool won = false;
        bool hasLost = false;
        for(int j = 0; j < n; j++){
            if (arr[i][j] == '+') won = true;
            if (arr[i][j] == '-') hasLost = true;
        }
        if(s[i] == '1' && hasLost){
            cout << "NO\n";
            return;
        }
        if(s[i] == '2' && !won){
            cout << "NO\n";
            return;
        }
    }
    cout << "YES" << endl;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cout << arr[i][j];
        }
        cout << endl;
    }
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    auto start = std::chrono::high_resolution_clock::now();
    int T;
    cin >> T;
    while(T--){
        solve();
    }
 
}
