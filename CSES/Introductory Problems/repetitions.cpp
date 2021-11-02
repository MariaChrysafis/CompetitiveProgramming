#include <iostream>
#include <algorithm>
#include <cstdio>
#define ll long long
using namespace std;
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string s;
    cin >> s;
    int best = 0;
    int cntr = 0;
    for(int i = 0; i < s.length() - 1; i++){
        if(s[i] == s[i + 1]){
            cntr++;
        }else{
            best = max(best,cntr + 1);
            cntr = 0;
        }
    }
    best = max(best, cntr + 1);
    cout << best << endl;
}
