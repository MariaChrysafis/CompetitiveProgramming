#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <iomanip>
#include <string>
#include <array>
#include <cassert>
#include <algorithm>
using namespace std;
void solve(){
    long long n, s;
    cin >> n >> s;
    cout << s/((n + 2)/2) << endl;
}
int main(){
    int t;
    cin >> t;
    while(t--) {
        solve();
    }
}
