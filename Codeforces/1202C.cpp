#include <algorithm>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <random>
#include <set>
#include <stack>
#include <vector>

#define ll long long
using namespace std;

ll eval(string s) {
    ll posx = 0;
    ll posy = 0;
    ll minx = 0;
    ll miny = 0;
    ll maxx = 0;
    ll maxy = 0;
    for (char c: s) {
        if (c == 'W') posy++;
        else if (c == 'S') posy--;
        else if (c == 'A') posx--;
        else if (c == 'D') posx++;
        maxx = max(maxx, posx);
        minx = min(minx, posx);
        maxy = max(maxy, posy);
        miny = min(miny, posy);
    }
    return (abs(maxx - minx) + 1) * (abs(maxy - miny) + 1);
}

ll solve(string s, char c) {
    ll myMin = eval(s);
    srand(time(NULL));
    ll t = 100;
    while (t--) {
        int ind = rand() % s.length();
        string t;
        t = s.substr(0, ind) + c + s.substr(ind, s.length() - ind);
        myMin = min(myMin, eval(t));
    }
    return myMin;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        string s;
        cin >> s;
        cout << min({solve(s, 'A'), solve(s, 'W'), solve(s, 'S'), solve(s, 'D')}) << '\n';
    }
}
