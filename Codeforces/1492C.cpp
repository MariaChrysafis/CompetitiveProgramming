#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <map>
#include <set>
using namespace std;
void print(vector<int> v){
    for(int i: v){
        cout << i << " ";
    }
    cout << endl;
}
string reverse(string s){
    string str;
    for(int i = 0; i < s.length() ; i++){
        str += s[s.length() - i - 1];
    }
    return str;
}
void solve(){
    int n, m;
    cin >> n >> m;
    string s, t;
    cin >> s >> t;
    vector<int> pref(t.length()), suf(t.length());
    int cur = 0;
    for(int i = 0; i < s.length(); i++){
        if(s[i] == t[cur]){
            pref[cur] = i;
            cur++;
        }
    }
    cur = t.length() - 1;
    for(int i = s.length() - 1; i >= 0; i--){
        if(s[i] == t[cur]){
            suf[cur] = i;
            cur--;
        }
    }
    int myMax = 0;
    for(int i = 0; i < t.length() - 1; i++){
        myMax = max(suf[i + 1] - pref[i], myMax);
    }
    cout << myMax << endl;
}
int main() {
    solve();
}
