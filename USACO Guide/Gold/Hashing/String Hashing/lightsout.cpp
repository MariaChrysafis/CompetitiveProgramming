#include <cmath>
#include <iostream>
#include <set>
#include <climits>
#include <cstdio>
#include <algorithm>
#include <cassert>
#include <string>
#include <vector>
#include <iomanip>
#include <unordered_map>
#include <type_traits>
#include <string>
#include <queue>
#include <map>

#define ll long long

using namespace std;
struct coord {
    int x;
    int y;
};
struct edge {
    coord c1;
    coord c2;
};

char pos(edge e) {
    if (e.c1.y == e.c2.y) {
        if (e.c1.x < e.c2.x) {
            return 'D';
        } else {
            return 'U';
        }
    }
    if (e.c1.x == e.c2.x) {
        if (e.c1.y < e.c2.y) {
            return 'L';
        } else {
            return 'R';
        }
    }
}

int length(edge e1) {
    return abs(e1.c1.x - e1.c2.x) + abs(e1.c1.y - e1.c2.y);
}

bool flip(edge e1, edge e3) {
    return pos(e1) == pos(e3);
}

int dist(vector<int> v) {
    int sum = 0;
    for (int i = 1; i < v.size(); i += 2) {
        sum += v[i];
    }
    return sum;
}

int main() {
    freopen("lightsout.in", "r", stdin);
    freopen("lightsout.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    vector<coord> v1;
    vector<edge> v2;
    for (int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        v1.push_back({a, b});
    }
    v2.push_back({v1[n - 1], v1[0]});
    for (int i = 0; i < n - 1; i++) {
        v2.push_back({v1[i], v1[i + 1]});
    }
    int angle[n];
    angle[0] = 1;
    for (int i = 1; i < n; i++) {
        bool b = flip(v2[(i - 1 + n) % n], v2[(i + 1) % n]);
        if (!b) {
            angle[i] = angle[i - 1];
        } else {
            angle[i] = !angle[i - 1];
        }
    }
    for (int i = 0; i < n; i++) {
        if (angle[i] == 0) angle[i] = -2;
        else angle[i] = -1;
    }
    int minDist[n];
    minDist[0] = 0;
    for (int i = 1; i < n; i++) {
        int dist1 = 0;
        for (int d = 0; i + d < n; d++) {
            dist1 += length(v2[(i + d + 1) % n]);
        }
        int dist2 = 0;
        for (int d = 0; d < i; d++) {
            dist2 += length(v2[(i - d) % n]);
        }
        minDist[i] = min(dist1, dist2);
    }
    vector<vector<int>> v(n);
    map<vector<int>, int> myMap;
    for (int i = 1; i < n; i++) {
        vector<int> myVec;
        myVec.push_back(angle[i]);
        myMap[myVec]++;
        for (int d = 0; d <= n / 2; d++) {
            //go from (i + d) to (i + d + 1)
            myVec.push_back(length(v2[(i + d + 1) % n]));
            myVec.push_back(angle[(i + d + 1) % n]);
            myMap[myVec]++;
        }
    }
    for (int i = 1; i < n; i++) {
        vector<int> myVec;
        myVec.push_back(angle[i]);
        for (int d = 0; d <= n / 2; d++) {
            myVec.push_back(length(v2[(i + d + 1) % n]));
            myVec.push_back(angle[(i + d + 1) % n]);
            if (myMap[myVec] == 1 || (i + d + 1) % n == 0) {
                v[i] = myVec;
                break;
            }
        }
    }
    int myMax = 0;
    for (int i = 1; i < n; i++) {
        int x = (v[i].size() - 1) / 2;
        myMax = max(dist(v[i]) + minDist[(i + x) % n] - minDist[i], myMax);
    }
    cout << myMax << endl;
    return 0;
}
