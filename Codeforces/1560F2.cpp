#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include <set>
#include <map>
 
#define ll long long
using namespace std;
int dist(string s){
    set<char> mySet;
    for(char c: s){
        mySet.insert(c);
    }
    return mySet.size();
}
string rec(string inp, int k, int ind, string num, int distinct){
    if(distinct > k || num.substr(0, ind) < inp.substr(0, ind) || inp[0] == '0'){
        return "";
    }
    if(ind == inp.length()){
        return num;
    }
    for(char c = '0'; c <= '9'; c++){
        num[ind] = c;
        string str = rec(inp, k, ind + 1, num, dist(num.substr(0, ind + 1)));
        if(!str.empty()){
            return str;
        }
    }
    return "";
}
 
string solve() {
    int n, k;
    cin >> n >> k;
    return rec(to_string(n), k, 0, to_string(n), 0);
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        string s = solve();
        cout << s << endl;
    }
}
