#include <iostream>
#include <vector>
#include <queue>
#include <set>
using namespace std;
void print(queue<char> q){
    while(!q.empty()){
        char x = q.front();
        cout << x << " ";
        q.pop();
    }
}
bool allEqual(char a, char b, char c){
    return (a == b && a ==c);
}
char mostFrequent(char a, char b, char c){
    if(a == b) return a;
    if(b == c) return b;
    if(a == c) return a;
    return '?';
}
bool rec(string s){
    if(s.length() == 1){
        return true;
    }
    int n = s.length();
    set<int> mySet;
    for(char c: s) mySet.insert(c);
    if(mySet.size() == 1) return false;
    vector<char> v(n);
    vector<int> nxt(n);
    for(int i = 0; i < s.length(); i++){
        v.push_back(s[i]);
    }
    for(int i = 0; i < n; i++){
        nxt[i] = i + 1;
    }
    nxt[n - 1] = -1;
    int pos = 0;
    while(pos < s.length()){
        if(nxt[pos] == -1 || nxt[nxt[pos]] == -1){
            pos++;
            continue;
        }
        if(s[pos] == '?' || s[nxt[pos]] == '?' || s[nxt[nxt[pos]]] == '?'){
            pos++;
            continue;
        }
        if(!allEqual(s[pos], s[nxt[pos]], s[nxt[nxt[pos]]])){
            s[pos] = mostFrequent(s[pos], s[nxt[pos]], s[nxt[nxt[pos]]]);
            s[nxt[pos]] = '?';
            s[nxt[nxt[pos]]] = '?';
            nxt[pos] = nxt[nxt[nxt[pos]]];
        }else{
            pos++;
        }
    }
    string str = "";
    for(int i = 0; i < s.length(); i++){
        if(s[i] != '?'){
            str += s[i];
        }
    }
    return rec(str);
}
bool solve(){
    int n;
    cin >> n;
    string s;
    cin >> s;
    bool b = rec(s);
    return b;
}
int main(){
    int t;
    cin >> t;
    for(int i = 0; i < t; i++){
        cout << "Case #" << i + 1 << ": ";
        bool b = solve();
        if(b){
            cout << "Y";
        }else{
            cout << "N";
        }
        if(i != t - 1){
            cout << "\n";
        }
    }
}
