#include <vector>
#include <algorithm>
#include <iostream>
#include <set>
#include <cmath>
#include <map>
#include <random>
#include <cassert>
#include <ctime>
#include <cstdlib>
#include <limits.h>
#include <queue>

using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string s;
    cin >> s;
    map<int,set<pair<char,char>>> cnt;
    int ans = 0;
    for (int i = 0; i < s.length(); i += 3) {
        if (s[i] == 'P') {
            cnt[0].insert({s[i + 1], s[i + 2]});
        } else if (s[i] == 'K') {
            cnt[1].insert({s[i + 1], s[i + 2]});
        } else if (s[i] == 'H') {
            cnt[2].insert({s[i + 1], s[i + 2]});
        } else if (s[i] == 'T') {
            cnt[3].insert({s[i + 1], s[i + 2]});
        }
    }
    ans = 0;
    for (int i = 0; i < 4; i++) {
        ans += cnt[i].size();
    }
    if (ans != s.length()/3) {
        cout << "GRESKA\n";
        return 0;
    }
    for (int i = 0; i < 4; i++) {
        cout << 13 - cnt[i].size() << ' ';
    }
}
