#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <map>
#include <set>
#include <queue>
using namespace std;
//long long
string yesNo(bool b){
    if(b) return "Yes";
    else return "No";
}
pair<int,int> read(){
    int a, b;
    cin >> a >> b;
    return {a, b};
}
void solve(){
    string s;
    cin >> s;
    int left = 0;
    int right = s.length() - 1;
    map<char,int> oc;
    map<char,int> cnt;
    for(char c = 'a'; c <= 'z'; c++){
        oc[c] = -1;
    }
    char myMax = 'a';
    for(int i = 0; i < s.length(); i++){
        oc[s[i]] = i;
        cnt[s[i]]++;
        myMax = max(s[i], myMax);
        if(cnt[s[i]] > 1){
            cout << "NO" << endl;
            return;
        }
    }
    for(char c = myMax; c >= 'a'; c--){
        if(oc[c] == left){
            left++;
        }else if(oc[c] == right){
            right--;
        }else{
            cout << "NO" << endl;
            return;
        }
    }
    if(left <= right){
        cout << "NO" << endl;
        return;
    }
    cout << "YES" << endl;
}
int main(){
    int t;
    cin >> t;
    while(t--){
        solve();
    }
}
