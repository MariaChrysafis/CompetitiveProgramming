#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <map>
#include <set>
using namespace std;
map<int,vector<int>> construct(vector<int> v){
    map<int,vector<int>> myMap;
    for(int i = 0; i < v.size(); i++){
        myMap[v[i]].push_back(i);
    }
    return myMap;
}
void solve(){
    int n, m;
    cin >> n >> m;
    int arr[m][26];
    for(int i = 0; i < m; i++){
        for(int j = 0; j < 26; j++){
            arr[i][j] = 0;
        }
    }
    for(int i = 0; i < n; i++){
        string s;
        cin >> s;
        for(int j = 0; j < m; j++){
            arr[j][s[j] - 'a']++;
        }
    }
    for(int i = 0; i < n - 1; i++){
        string s;
        cin >> s;
        for(int j = 0; j < m; j++){
            arr[j][s[j] - 'a']--;
        }
    }
    map<int,char> conv;
    for(char c = 'a'; c <= 'z'; c++){
        conv[c - 'a'] = c;
    }
    for(int i = 0; i < m; i++){
        for(int j = 0; j < 26; j++){
            if(arr[i][j] == 1){
                cout << conv[j];
            }
        }
    }
    cout << endl;
}
int main() {
    int t;
    cin >> t;
    while(t--){
        solve();
    }
}
