#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <cassert>
#include <set>
#include <map>
#include <algorithm>
#include <ctime>
#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")
typedef long long ll;

using namespace std;

set<string> func (int orig, int delta) {
    int cur = orig;
    string s = "";
    set<string> mySet;
    while (cur < 10 && mySet.size() <= 20 && cur >= 0) {
        s += ('0' + cur);
        mySet.insert(s);
        cur += delta;
    }
    return mySet;
}

ll to_ll (string s) {
    vector<ll> powr = {1};
    while (powr.size() != 18) {
        powr.push_back(powr.back() * 10);
    }
    ll ans = 0;
    for (int i = 0; i < s.length(); i++) {
        //cout << s[i] - '0' << " " << powr[s.length() - i - 1] << '\n';
        ans += (s[i] - '0') * powr[s.length() - i - 1];
    }
    return ans;
}

auto cmp = [](const string& x, const string& y) { return to_ll(x) < to_ll(y); };


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    set<string,bool(*)(const string&,const string&)> mySet(cmp);

    for (int i = 1; i < 10; i++) {
        for (int j = -9; j < 10; j++) {
            for (string myString: func(i, j)) {
                mySet.insert(myString);
            }
        }
    }

    //cout << to_ll("5005553") << '\n';
    string s;
    cin >> s;
    auto it = mySet.lower_bound(s);
    cout << *it;


}
