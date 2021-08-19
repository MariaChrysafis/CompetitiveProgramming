#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include <set>
#include <map>
 
#define ll long long
using namespace std;
 
int longestCommonSubsequence(string a, string b) {
    swap(a,b );
    int ind = 0;
    for(int i = 0; i < b.length(); i++){
        if(a[ind] == b[i]){
            ind++;
        }
    }
    return ind;
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    vector<string> powr;
    vector<long long> p;
    p.push_back(1), powr.push_back("1");
    for(int i = 0; i <= 60; i++){
        p.push_back(p.back() * 2);
        powr.push_back(to_string(p.back()));
    }
    int t;
    cin >> t;
    while(t--){
        string s;
        cin >> s;
        int ans = 1e9;
        for(int i = 0; i < powr.size(); i++){
            int x = -2 * longestCommonSubsequence(s, powr[i]) + s.length() + powr[i].length();
            ans = min(x, ans);
        }
        cout << ans << endl;
    }
 
}
