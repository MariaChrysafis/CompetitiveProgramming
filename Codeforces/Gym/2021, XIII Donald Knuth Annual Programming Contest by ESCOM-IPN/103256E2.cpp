#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <cmath>
#include <set>
#define ll long long
using namespace std;
void print(vector<int> v){
    for(int i: v) cout << i << " ";
    cout << endl;
}
int find_index(vector<int> v, int val){
    for(int i = 0; i < v.size(); i++){
        if(v[i] == val){
            return i;
        }
    }
    return -1;
}
vector<int> reverse(vector<int> v, int pref){
    cout << pref + 1 << " ";
    reverse(v.begin(), v.begin() + pref + 1);
    return v;
}
int n;
vector<string> pos;
void rec(string s){
    if(s.length() == n){
        pos.push_back(s);
        return;
    }
    rec(s + 'A');
    rec(s + 'S');
}
char rev(char c){
    if(c == 'A') return 'S';
    if(c == 'S') return 'A';
}
long long gcd(long long a, long long b){
    if(min(a,b) == 0) return max(a, b);
    return gcd(max(a, b) % min(a, b), min(a,b));
}
void solve(){
    cin >> n;
    long long x = n * (n + 1);
    long long y = 4;
    while(x % 2 == 0 && y % 2 == 0){
        x /= 2;
        y /= 2;
    }
    //cout << n * (n + 1) << " " << 4 << endl;
    cout << x << '/' << y << "\n";
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
}
