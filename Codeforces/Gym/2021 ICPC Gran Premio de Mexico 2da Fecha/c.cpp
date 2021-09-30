#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <fstream>

using namespace std;
const int INF = 1e9;
void solve() {
    string s;
    cin >> s;
    int myMin = 0;
    int oc = -1;
    int cur = 0;
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == 'R') {
            cur--;
            if(cur < myMin) {
                myMin = cur;
                oc = i;
            }
        } else {
            cur++;
        }
        //cout << cur << " ";
    }
    cout << oc + 1 << endl;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }

}
