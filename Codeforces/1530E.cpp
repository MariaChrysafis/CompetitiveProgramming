#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
 
using namespace std;
 
using ll = long long;
string reverse(string s){
    reverse(s.begin(), s.end());
    return s;
}
string sorted(string s){
    sort(s.begin(), s.end());
    return s;
}
void solve(){
    string s;
    cin >> s;
    sort(s.begin(), s.end());
    //map<char,int> oc;
    set<char> mySet;
    for(char c: s) mySet.insert(c);
    if(sorted(reverse(s)) == reverse(sorted(s))){
        cout << s << endl;
        return;
    }
    map<char,int> oc;
    for(char c: s) oc[c]++;
    for(char c = 'a'; c <= 'z'; c++){
        if(oc[c] == 1){
            cout << c;
            for(int i = 0; i < s.length(); i++){
                if(s[i] != c){
                    cout << s[i];
                }
            }
            cout << endl;
            return;
        }
    }
    if(oc[s[0]] - 1 > s.length() - oc[s[0]] + (s.length() % 2 == 0)){
        if(mySet.size() == 2){
            sort(s.begin(), s.end());
            reverse(s.begin(), s.end());
            int d = s.length() - 1;
            reverse(s.begin(), s.begin() + d);
            reverse(s.begin() + d, s.end());
            reverse(s.begin(), s.end());
            cout << s << endl;
            return;
        }
        oc[s[0]]--;
        cout << s[0];
        for(char c = 'a'; c <= 'z'; c++){
            if(c != s[0] && oc[c] >= 1){
                cout << c;
                oc[c]--;
                break;
            }
        }
        while(oc[s[0]] > 0){
            cout << s[0];
            oc[s[0]]--;
        }
        string str;
        for(char c = 'a'; c <= 'z'; c++){
            while(oc[c] >= 1){
                str += c;
                oc[c]--;
            }
        }
        int ind = 0;
        for(int i = 0; i < str.length(); i++){
            if(str[i] > str[0]){
                ind = i;
                break;
            }
        }
        swap(str[0], str[ind]);
        cout << str;
        cout << endl;
        return;
    }
    cout << s[0] << s[0];
    oc[s[0]]--, oc[s[0]]--;
    vector<char> v;
    for(char c = 'a'; c <= 'z'; c++){
        if(oc[c] >= 1){
            v.push_back(c);
        }
    }
    char prev = s[0];
    for(int i = 0; i < s.length() - 2; i++){
        for(char j = 'a'; j <= 'z'; j++){
            if(j == prev && prev == s[0]) continue;
            if(oc[j] >= 1){
                cout << j;
                oc[j]--;
                prev = j;
                break;
            }
        }
    }
    cout << endl;
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
