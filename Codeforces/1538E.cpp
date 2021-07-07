#include <vector>
#include <iostream>
#include <cmath>
#include <map>
#include <set>
#include <algorithm>
using namespace std;
struct String{
    long long hello;
    string suf;
    string pref;
    bool operator<(const String s1)const{
        return (s1.hello < this->hello);
    }
};
struct solve{
    map<string,String> myMap;
    static int occurencesOfHaha(string s){
        int cntr = 0;
        for(int i = 0; i + 3 < s.length(); i++){
            if(s[i] == 'h' && s[i + 1] == 'a' && s[i + 2] == 'h' && s[i + 3] == 'a'){
                cntr++;
            }
        }
        return cntr;
    }
    static string Prefix(string s, int x){
        if(s.length() <= x) return s;
        string s1;
        for(int i = 0; i < x; i++) s1 += s[i];
        return s1;
    }
    static string Suffix(string s, int x){
        if(s.length() <= x) return s;
        string s1;
        for(int i = 0; i < x; i++) s1 += s[s.length() - i - 1];
        reverse(s1.begin(), s1.end());
        return s1;
    }
    static String generate(string s){
        String str;
        str.hello = occurencesOfHaha(s);
        str.suf = Suffix(s, 3);
        str.pref = Prefix(s, 3);
        return str;
    }
    static String merge(String a, String b){
        String str;
        str.pref = Prefix(a.pref + b.pref, 3);
        str.suf = Suffix(a.suf + b.suf, 3);
        str.hello = a.hello + b.hello + occurencesOfHaha(a.suf + b.pref);
        return str;
    }
    void read(){
        int n;
        cin >> n;
        string s;
        for(int i = 0; i < n; i++){
            cin >> s;
            string dum;
            cin >> dum;
            if(dum == ":="){
                string a;
                cin >> a;
                myMap[s] = generate(a);
            }else if(dum == "="){
                string a, dummy, c;
                cin >> a >> dummy >> c;
                myMap[s] = merge(myMap[a], myMap[c]);
            }
            //cout << myMap[s].pref << " " << myMap[s].suf << " " << myMap[s].hello << endl;
        }
        cout << myMap[s].hello << endl;
    }
};
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin >> t;
    while(t--){
        solve s;
        s.read();
    }
}
