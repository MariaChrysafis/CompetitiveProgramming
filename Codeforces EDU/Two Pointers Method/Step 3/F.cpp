#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <queue>
#include <cassert>

using namespace std;

void solve() {
    long long n, m;
    cin >> n >> m;
    string s;
    cin >> s;
    string letters;
    cin >> letters;
    map<char, long long> oc_letters;
    for (char c: letters) {
        oc_letters[c]++;
    }
    long long strt = -1;
    for (int i = 0; i < s.length(); i++) {
        if (oc_letters[s[i]]) {
            strt = i;
            break;
        }
    }
    if (strt == -1) {
        cout << 0;
        return;
    }
    long long l = strt;
    long long r = strt;
    map<char, long long> myMap;
    myMap[s[strt]]++;
    long long upTo[n];
    for(int i = 0; i < n; i++) {
        upTo[i] = i - 1;
    }
    while (r != n - 1) {
        if (myMap[s[r + 1]] + 1 <= oc_letters[s[r + 1]]) {
            r++;
            myMap[s[r]]++;
        } else {
            upTo[l] = r;
            myMap[s[l]]--;
            l++;
        }
    }
    while (l != n) {
        upTo[l] = n - 1;
        l++;
    }
    long long ans = 0;
    for (long long i = 0; i < n; i++) {
        ans += upTo[i] - i + 1;
    }
    cout << ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();

}
