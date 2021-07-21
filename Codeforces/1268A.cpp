#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <cmath>
#define ll long long
using namespace std;
string s;
int n, k;
bool valid(int m){
    string str = s;
    vector<char> identity(m);
    for(int i = 0; i < m; i++){
        identity[i] = s[i];
    }
    for(int i = 0; i < s.length(); i++){
        if(i % k < m){
            str[i] = identity[i % k];
        }else{
            str[i] = '9';
        }
        //cout << str << endl;
    }
    return (str > s);
}
int binSearch(int l, int r){
    //cout << l << " " << r << '\n';
    if(l == r){
        return l;
    }
    int m = (l + r + 1)/2;
    if(valid(m)){
        return binSearch(m, r);
    }else{
        return binSearch(l, m - 1);
    }
}
bool done(string str){
    vector<set<int>> v(k);
    for(int i = 0; i < str.length(); i++){
        v[i %k ].insert(str[i]);
        if(v[i % k].size() > 1) return false;
    }
    return true;
}
void solve(){
    cin >> n >> k;
    cin >> s;
    if(done(s)){
        cout << s.length() << endl;
        cout << s << endl;
        return;
    }
    int x = binSearch(0, k);
    string str;
    while(str.size() != s.size()){
        str += '?';
    }
    for(int i = 0; i < str.length(); i++){
        if(i % k < x){
            str[i] = s[i % k];
        }else{
            str[i] = s[i % k]+1;
            if(str[i] == ':') str[i] = '0';
        }
    }
    cout << str.length() << endl;
    cout << str << endl;
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
}
