#include <cmath>
#include <iostream>
#include <set>
#include <climits>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <type_traits>
#include <string>
#include <queue>
#include <map>
using namespace std;
long long myMap[26][7];
long long solve (int x) {
    vector<int> v(7);
    vector<char> letters = {'B', 'E', 'S', 'I', 'G', 'O', 'M'};
    for (int i = 0; i < 7; i++) {
        v[i] = x % 7;
        x /= 7;
    }
    map<char,int> var;
    for (int i = 0; i < v.size(); i++) {
        var[letters[i]] = v[i];
    }
    if ((var['B'] + 2 * var['E'] + var['I'] + 2 * var['S'] + (int)7e5) % 7 != 0 &&
            (var['G'] + var['O'] + var['E'] + var['S'] + (int)7e5) % 7 != 0 &&
            (var['M'] + 2 * var['O'] + (int)7e5) % 7 != 0) {
        return 0;
    }
    long long cnt = 1;
    for (char c: letters) {
        cnt *= myMap[c - 'A'][var[c]];
    }
    return cnt;
}
int main() {
    freopen("bgm.in", "r", stdin);
    freopen("bgm.out", "w", stdout);
    int t;
    cin >> t;
    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < 7; j++) {
            myMap[i][j] = 0;
        }
    }
    while (t--) {
        char c;
        int x;
        cin >> c >> x;
        x += (int)7e5;
        myMap[c - 'A'][x % 7]++;
    }
    long long ans = 0;
    for (int i = 0; i < pow(7, 7); i++) {
        ans += solve(i);
    }
    cout << ans << endl;
}
