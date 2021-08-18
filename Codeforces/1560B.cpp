#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include <set>
#include <map>
 
#define ll long long
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    vector<int> v;
    for(int i = 0; i < 2000; i++){
        if(i % 3 == 0) continue;
        string s = to_string(i);
        if(s[s.length() - 1] == '3') continue;
        v.push_back(i);
    }
    int t;
    cin >> t;
    while(t--){
        int a, b, c;
        cin >> a >> b >> c;
        int n = 2 * max(a, b) - 2 * min(a,b);
        if(a < b) swap(a, b);
        int x = a - b + c;
        if(c > n/2) x = c + b - a;
        if(x <= n && x >= 1 && n >= a && n >= b && n >= c) cout << x << endl;
        else cout << -1 << endl;
    }
}
