#include <iostream>
#include <map>
#include <vector>
using namespace std;
struct alphabet{
    vector<map<char,long>> myMap;
    string s;
    long convert(map<char, long> inp){
        int ans = 0;
        for(char c = 'a'; c <= 'z'; c++){
            ans += inp[c] * (c - 'a' + 1);
        }
        return ans;
    }
    long interval(long x, long y){
        map<char,long> ans;
        for(char c = 'a'; c <= 'z'; c++){
            ans[c] = myMap[y + 1][c] - myMap[x][c];
        }
        return convert(ans);
    }
    void query(int l, int r){
        cout << interval(l, r) << endl;
    }
    void fill(){
        map<char,long> cur;
        myMap.push_back(cur);
        for(char c: s){
            cur[c]++;
            myMap.push_back(cur);
        }
        //cout << s.length() << endl;
        //cout << myMap.size() << endl;
    }
};
void solve(){
    int n, q;
    cin >> n >> q;
    string s;
    cin >> s;
    //cout << s << endl;
    alphabet alph;
    alph.s = s;
    alph.fill();
    while(q--){
        long l, r;
        cin >> l >> r;
        l--, r--;
        //cout << l << " " << r << endl;
        alph.query(l, r);
    }
}
int main(){
    solve();
}
