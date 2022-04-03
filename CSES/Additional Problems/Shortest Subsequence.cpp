#include <vector>
#include <algorithm>
#include <iostream>
#include <set>
#include <cmath>
#include <map>
#include <random>
#include <cassert>
#include <ctime>
#include <bitset>
#include <stack>
#include <cstdlib>
#include <queue>
#include <stdint.h>
#include <vector>
#include <cassert>
#include <numeric>
#include <iostream>
#include <algorithm>
#include <functional>
#include <cstdio>
#include <limits.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string s;
    cin >> s;
    set<char> mySet;
    string cur = "";
    for (int i = 0; i < s.length(); i++) {
        if (!mySet.count(s[i]) && mySet.size() == 3) {
            mySet.clear();
            cur += s[i];
        } else {
            mySet.insert(s[i]);
        }
    }
    for (char c: {'A', 'C', 'G', 'T'}) {
        if (!mySet.count(c)) {
            cur += c;
            break;
        }
    }
    cout << cur;
}
