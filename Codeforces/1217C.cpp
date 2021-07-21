#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <cmath>
#define ll long long
using namespace std;
const int MAX = 2e5 + 10;
bool isPowerOfTwo(int x){
    int y = log2(x);
    return (pow(2, y) == x);
}
int firstOccurenceOf1(string s){
    for(int i = 1; i < s.length(); i++){
        if(s[i] == '1'){
            return i;
        }
    }
    return -1;
}
int convertToInt(string s){
    //reverse(s.begin(), )
    int powr = 1;
    int ans = 0;
    for(int i = s.length() - 1; i >= 0; i--){
        if(s[i] == '1'){
            ans += powr;
        }
        powr *= 2;
    }
    return ans;
}
vector<vector<int>> crux;
void solve(){
    string s;
    cin >> s;
    vector<int> pntr(s.length());
    for(int i = 0; i < s.length(); i++){
        pntr[i] = -1;
    }
    pntr[0] = firstOccurenceOf1(s);
    for(int i = 1; i < s.length(); i++){
        if(s[i] == '0'){
            pntr[i] = pntr[i - 1];
        }else{
            for(int j = i + 1; j < s.length(); j++){
                if(s[j] == '1'){
                    pntr[i] = j;
                    break;
                }
            }
        }
    }
    long long ans = 0;
    for(int i = 0; i < s.length(); i++){
        if(s[i] == '1' || pntr[i] == -1){
            continue;
        }
        int len = pntr[i] - i;
        for(int j: crux[len]){
            bool fine = false;
            string str = "";
            for(int k = pntr[i]; k < min(pntr[i] + 18, (int)s.length()); k++){
                str += s[k];
                if(convertToInt(str) == j){
                    fine = true;
                }
            }
            ans += fine;
        }
    }
    for(char c: s){
        if(c == '1') ans++;
    }
    for(int i = 0; i < s.length() - 1; i++){
        if(s[i] == '1' && s[i + 1] == '0'){
            ans++;
        }
    }
    cout << ans << endl;
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    crux.resize(MAX);
    crux[0].push_back({});
    int cur = 3;
    for(int i = 1; i < MAX; i++){
        crux[i].push_back(cur);
        cur++;
        if(isPowerOfTwo(cur)){
            crux[i].push_back(cur), cur++;
        }
    }
    int t;
    cin >> t;
    while(t--) {
        solve();
    }
}
