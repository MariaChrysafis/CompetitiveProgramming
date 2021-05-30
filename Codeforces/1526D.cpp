#include <iostream>
#include <queue>
#include <map>
using namespace std;
vector<string> pos = {"AONT", "AOTN", "ATNO", "ATON", "ANTO", "ANOT", "NAOT", "NATO", "NOAT", "NOTA", "NTAO", "NTOA", "OANT", "OATN", "ONAT", "ONTA", "OTAN", "OTNA", "TANO", "TAON", "TNAO", "TNOA", "TOAN", "TONA"};
map<char,int> oc;
string solver(string v){
    string str;
    for(char c: v){
        int x = oc[c];
        for(int i = 0; i < x; i++){
            str += c;
        }
    }
    return str;
}
long long inv(string s, string ordering){
    int myMap[26];
    map<char,int> val;
    map<int,char> inv;
    for(int i = 0; i < ordering.length(); i++) val[ordering[i]] = i, inv[i] = ordering[i], myMap[ordering[i] - 'A'] = 0;
    long long ans = 0;
    for(int i = 0; i < s.length(); i++){
        myMap[s[i] - 'A']++;
        for(int j = 0; j < val[s[i]]; j++){
            ans += myMap[inv[j] - 'A'];
        }
    }
    return (s.length() * (s.length() - 1)/2) - ans;
}
void solve(string s){
    oc.clear();
    for(char c: s){
        oc[c]++;
    }
    long long myMax = -1;
    string best = "";
    string ans;
    for(string myStr: pos){
        long long x = inv(s, myStr);
        if(x > myMax){
            ans = myStr;
            myMax = x;
        }
    }
    cout << solver(ans) << endl;
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while(t--){
        string myStr;
        cin >> myStr;
        solve(myStr);
    }
}
