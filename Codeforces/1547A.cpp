#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <map>
#include <set>
#include <queue>
using namespace std;
//long long
string yesNo(bool b){
    if(b) return "Yes";
    else return "No";
}
pair<int,int> read(){
    int a, b;
    cin >> a >> b;
    return {a, b};
}
void solve(){
    pair<int,int> a, b, f;
    a = read(), b = read(), f = read();
    if(a.first == b.first && b.first == f.first && ((f.second > a.second && f.second < b.second) || (f.second < a.second && f.second > b.second))){
        cout << abs(a.first - b.first) + abs(a.second - b.second) + 2 << '\n';
    }else if(a.second == b.second && b.second == f.second && ((f.first > a.first && f.first < b.first) || (f.first < a.first && f.first > b.first))){
        cout << abs(a.first - b.first) + abs(a.second - b.second) + 2 << '\n';
    }else{
        cout << abs(a.first - b.first) + abs(a.second - b.second) << '\n';
    }
}
int main(){
    int t;
    cin >> t;
    while(t--){
        solve();
    }
}
