#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <cmath>
#include <stack>
using namespace std;
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while(t--){
        string s, t;
        cin >> s >> t;
        if(s.length() < t.length()) {
            cout << "NO\n";
            continue;
        }
        int ind = 0;
        int des = (s.length() - t.length()) % 2;
        for(int i = 0; i < s.length(); i++){
            if(s[i] == t[ind] && i % 2 == des){
                ind++, des++, des %= 2;
                if(ind == t.length()){
                    cout << "YES\n";
                    break;
                }
 
            }
        }
        if(ind != t.length()) cout << "NO\n";
    }
}
