#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;
bool solve(){
    int n;
    cin >> n;
    string s;
    cin >> s;
    map<char,vector<int>> myMap;
    for(int i = 0; i < s.length(); i++){
        myMap[s[i]].push_back(i);
    }
    for(char c = 'A'; c <= 'Z'; c++){
        vector<int> v = myMap[c];
        if(v.size() == 0) continue;
        for(int i = 0; i < v.size() - 1; i++){
            int x = v[i];
            //cout << i + 1 << " " << myMap[c].size() << endl;
            int y = v[i + 1];
            if(y - x != 1) return false;
        }
    }
    return true;
}
int main(){
    int t;
    cin >> t;
    while(t--){
        bool b = solve();
        if(b) cout << "YES" << endl;
        else cout << "NO" << endl;
    }
}
