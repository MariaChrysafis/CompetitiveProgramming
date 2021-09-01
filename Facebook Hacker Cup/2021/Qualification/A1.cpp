#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <map>
using namespace std;
void print(queue<char> q){
    while(!q.empty()){
        char x = q.front();
        cout << x << " ";
        q.pop();
    }
}
bool isVowel(char c){
    return (c == 'A' || c == 'I' || c == 'O' || c == 'U' || c == 'E');
}
void solve(){
    string s;
    cin >> s;
    int myMin = 1e9;
    for(char c = 'A'; c <= 'Z'; c++){
        bool v1 = isVowel(c);
        int cntr = 0;
        for(char d: s){
            bool v2 = isVowel(d);
            if(c == d) continue;
            if(v1 == v2) cntr += 2;
            else cntr += 1;
        }
        //cout << cntr << " ";
        myMin = min(myMin, cntr);
    }
    cout << myMin;
}
int main(){
    int t;
    cin >> t;
    for(int i = 0; i < t; i++){
        cout << "Case #" << i + 1 << ": ";
        solve();
        //cout << x;
        if(i != t - 1){
            cout << "\n";
        }
    }
}
