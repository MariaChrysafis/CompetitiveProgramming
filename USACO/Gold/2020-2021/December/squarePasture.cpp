#include <iostream>
#include <vector>
#include <cassert>
#include <map>
#include <set>
#include <chrono>

#include <queue>
#include <algorithm>
#include <cmath>
#include <fstream>

#pragma GCC optimize("O2")
using namespace std;

int read() {
    int x;
    cin >> x;
    return x;
}

struct coord {
    int x;
    int y;
};

bool equals (coord c1, coord c2) {
    return (c1.x == c2.x && c1.y == c2.y);
}

bool compX(coord c1, coord c2) {
    return c1.x < c2.x;
}

vector<coord> vec;
int eq = 0;
int solve () {
    int ans = 0;
    for (int left = 0; left < vec.size(); left++) {
        for (int right = left + 1; right < vec.size(); right++) {
            int len = abs(vec[left].x - vec[right].x);
            if (len < abs(vec[left].y - vec[right].y)) {
                continue;
            }
            int upmost = min(vec[left].y, vec[right].y) + len;
            int downmost = max(vec[left].y, vec[right].y) - len;
            set<int> s;
            s.insert(upmost);
            set<int> valid;
            valid.insert(vec[left].y), valid.insert(vec[right].y);
            for (int i = 0; i < vec.size(); i++) {
                coord myCoord = vec[i];
                if (equals(myCoord, vec[left]) || equals(myCoord, vec[right])) {
                    continue;
                }
                if(myCoord.x > max(vec[left].x, vec[right].x) || myCoord.x < min(vec[left].x, vec[right].x)) {
                    continue;
                }
                if (myCoord.y >= min(vec[left].y, vec[right].y) && myCoord.y <= max(vec[left].y, vec[right].y)) {
                    continue;
                }
                if (myCoord.y >= downmost && myCoord.y <= min(vec[left].y, vec[right].y)) {
                    s.insert(myCoord.y + len), valid.insert(myCoord.y);
                }
                if (myCoord.y <= upmost && myCoord.y >= max(vec[left].y, vec[right].y)) {
                    s.insert(myCoord.y - 1), valid.insert(myCoord.y);
                }
            }
            for (int i: valid) {
                eq += valid.count(i + len);
            }
            int cntr = 0;
            for (int j: s) {
                cntr += (j <= upmost && j >= max(vec[left].y, vec[right].y));
            }
            ans += cntr;
        }
    }
    return ans;
}

int main() {
    int n = read();
    for (int i = 0; i < n; i++) {
        vec.push_back((coord) {read(), read()});
    }
    sort (vec.begin(), vec.end(), compX);
    int ans = n + 1;
    ans += solve();
    for (int i = 0; i < vec.size(); i++) {
        swap(vec[i].x, vec[i].y);
    }
    sort (vec.begin(), vec.end(), compX);
    ans += solve();
    cout << ans - eq/2 << endl;
}
