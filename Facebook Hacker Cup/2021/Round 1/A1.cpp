#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

const int INF = 1e9;
void solve() {
    int n;
    cin >> n;
    string s;
    cin >> s;
    vector<int> cur(2);
    vector<int> prev(2);
    prev[0] = prev[1] = INF;
    if(s[0] == 'F') prev[0] = prev[1] = 0;
    else if(s[0] == 'O') prev[1] = 0;
    else if(s[0] == 'X') prev[0] = 0;
    for(int i = 1; i < s.length(); i++){
        cur[0] = cur[1] = INF;
        if(s[i] == 'F'){
            cur[0] = min(prev[1] + 1, prev[0]);
            cur[1] = min(prev[1], prev[0] + 1);
        }else if(s[i] == 'O'){
            cur[1] = min(prev[1], prev[0] + 1);
        }else{
            cur[0] = min(prev[1] + 1, prev[0]);
        }
        prev = cur;
    }
    cout << min(cur[0], cur[1]);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    for (int i = 1; i <= t; i++) {
        cout << "Case #" << i << ": ";
        solve();
        cout << '\n';
    }

}
