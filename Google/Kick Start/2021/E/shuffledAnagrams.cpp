#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;
bool comp(pair<char,int> p1, pair<char,int> p2){
    return (p1.second > p2.second);
}
bool valid(string s1, string s2){
    for(int i = 0; i < s1.length(); i++){
        if(s1[i] == s2[i]){
            return false;
        }
    }
    return true;
}
const int INF = 1e9;
string solve(string inp){
    string orig = inp;
    map<char,int> oc;
    for(char c: inp) {
        oc[c]++;
    }
    for(int i = 0; i < inp.length(); i++){
        char c = inp[i];
        for(int j = 0; j < 26; j++){
            if(c == 'z') c = 'a';
            else c++;
            if(oc[c]){
                oc[c]--;
                inp[i] = c;
                break;
            }
        }
    }
    if(valid(orig, inp)) return inp;
    for(int i = 0; i < orig.length(); i++){
        if(orig[i] == inp[i]){
            for(int j = 0; j < orig.length(); j++){
                if(j == i) continue;
                if(orig[j] != inp[i] && orig[i] != inp[j]){
                    swap(inp[i], inp[j]);
                    break;
                }
            }
        }
    }
    if(valid(orig, inp)) return inp;
    //cout << inp << endl;
    return "IMPOSSIBLE";
}
int main(){
    int t;
    cin >> t;
    for(int i = 0; i < t; i++){
        string s;
        cin >> s;
        string str = solve(s);
        cout << "Case #" << i + 1 << ": " << str << '\n';
    }
}
