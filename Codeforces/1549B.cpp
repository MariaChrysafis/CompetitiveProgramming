#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <cmath>
#include <map>
#define ll long long
using namespace std;
void print(vector<int> v){
    for(int i: v){
        cout << i << " ";
    }
    cout << endl;
}
void print(vector<long long> v){
    for(long long i: v){
        cout << i << " ";
    }
    cout << endl;
}
int gcd(int a, int b){
    if(min(a,b) == 0) return max(a,b);
    return gcd(max(a,b) % min(a,b), min(a,b));
}
void solve(){
    int n;
    cin >> n;
    string s1, s2;
    cin >> s1 >> s2;
    swap(s1, s2);
    int cntr = 0;
    for(int i = 0; i < s1.length(); i++){
        if(s1[i] == '1'){
            if(i > 0 && s2[i - 1] == '1') cntr++;
            else if(s2[i] == '0') cntr++, s2[i] = '2';
            else if(i + 1 < s2.length() && s2[i + 1] == '1') cntr++, s2[i + 1] = '2';
        }
    }
    cout << cntr << endl;
}
int main(){
    int t;
    cin >> t;
    while(t--){
        solve();
    }
}
