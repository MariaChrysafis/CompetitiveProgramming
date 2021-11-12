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

#define ll long long

#include <map>

using namespace std;

struct Coord {
    int x, y;

    int dist(Coord c) {
        return abs(c.x - x) + abs(c.y - y);
    }
};

int main() {
    freopen("marathon.in", "r", stdin);
    freopen("marathon.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N, Q;
    cin >> N >> Q;
    vector<Coord> vec(N);
    vector<int> gain(N); //how much will we gain by skipping this interval (maximal lost cost)
    for (int i = 0; i < N; i++) {
        cin >> vec[i].x >> vec[i].y;
        gain[i] = 0;
    }
    vector<int> dist(N + 1); //distance if we use the first X courses
    dist[0] = dist[1] = 0;
    for (int i = 2; i <= N; i++) {
        dist[i] = dist[i - 1] + (vec[i - 1].dist(vec[i - 2]));
    }
    for (int i = 1; i < N; i++) {
        gain[i] = vec[i - 1].dist(vec[i + 1]) - vec[i - 1].dist(vec[i]) - vec[i].dist(vec[i + 1]);
    }
    while (Q--) {
        char c;
        cin >> c;
        if (c == 'Q') {
            int i, j;
            cin >> i >> j;
            int base = dist[j] - dist[i];
            i--, j--;
            int myMin = 0;
            for (int k = i + 1; k <= j - 1; k++) {
                myMin = min(myMin, gain[k]);
            }
            cout << base + myMin << '\n';
        } else {
            int ind, x, y;
            cin >> ind >> x >> y;
            ind--;
            //update ind + 1 ... N
            if (ind >= 0) {
                for (int i = ind + 1; i <= N; i++) {
                    dist[i] += vec[ind - 1].dist({x, y}) - vec[ind - 1].dist(vec[ind]);
                }
            }
            for (int i = ind + 2; i <= N; i++) {
                dist[i] += vec[ind + 1].dist({x, y}) - vec[ind + 1].dist(vec[ind]);
            }

            vec[ind] = {x, y};
            for (int i = ind - 1; i <= ind + 1; i++) {
                if (i - 1 >= 0 && i + 1 < gain.size()) {
                    gain[i] = vec[i - 1].dist(vec[i + 1]) - vec[i].dist(vec[i - 1]) - vec[i].dist(vec[i + 1]);
                }
            }
        }
    }
}
