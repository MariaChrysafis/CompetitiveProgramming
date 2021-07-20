#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#define ll long long
using namespace std;
void print(vector<pair<ll, ll>> v){
    for(pair<ll, ll> p: v){
        cout << p.first << " " << p.second << endl;
    }
}
void solve(){
    int n;
    cin >> n;
    string s;
    cin >> s;
    bool valid[n];
    for(int i = 0; i < n; i++) valid[i] = true;
    int prev[n];
    int next[n];
    for(int i = 0; i < n; i++) prev[i] = i - 1, next[i] = i + 1;
    next[n - 1] = prev[0] = -1;
    int cntr = 0;
    for(char c = 'z'; c >= 'a'; c--){
        char d = c;
        d--;
        for(int i = 0; i < s.length(); i++){
            if(valid[i] && s[i] == c){
                if((next[i] != -1 && s[next[i]] == d) || (prev[i] != -1 && s[prev[i]] == d)) valid[i] = false;
                if(!valid[i]){
                    cntr++;
                    for(int j = 0; j < s.length(); j++){
                        if(next[j] == i) next[j] = next[i];
                        if(prev[j] == i) prev[j] = prev[i];
                    }
                }
            }
        }
        for(int i = s.length() - 1; i >= 0; i--){
            if(valid[i] && s[i] == c){
                if((next[i] != -1 && s[next[i]] == d) || (prev[i] != -1 && s[prev[i]] == d)) valid[i] = false;
                if(!valid[i]){
                    cntr++;
                    for(int j = 0; j < s.length(); j++){
                        if(next[j] == i) next[j] = next[i];
                        if(prev[j] == i) prev[j] = prev[i];
                    }
                }
            }
        }
    }
    cout << cntr << '\n';
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
}
