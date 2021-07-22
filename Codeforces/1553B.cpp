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
bool solve(){
    string s;
    string t;
    cin >> s >> t;
    for(int i = 0; i < s.length(); i++){
        for(int left = 0; left <= s.length(); left++){
            for(int right = 0; right <= s.length(); right++){
                if(left + right != t.length() - 1) continue;
                if(right + i >= s.length()) continue;
                string ans = "";
                int cur = i;
                ans += s[i];
                while(cur != right + i){
                    cur++;
                    ans += s[cur];
                }
                int orig = cur;
                while(cur >= 0 && cur != orig - left){
                    cur--;
                    if(cur >= 0) ans += s[cur];
                }
                if(ans == t){
                    return true;
                }
            }
        }
    }
    return false;
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while(t--){
        bool b = solve();
        if(b) cout << "YES\n";
        else cout << "NO\n";
    }
}
