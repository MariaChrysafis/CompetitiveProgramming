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
    int dist (Coord c) {
        return abs(c.x - x) + abs(c.y - y);
    }
};
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N, Q;
    cin >> N >> Q;
    vector<Coord> vec(N);
    for (int i = 0; i < N; i++) {
        cin >> vec[i].x >> vec[i].y;
    }
    vector<int> dist(N + 1); //distance if we use the first X courses
    dist[0] = dist[1] = 0;
    for (int i = 2; i <= N; i++) {
        dist[i] = dist[i - 1] + (vec[i - 1].dist(vec[i - 2]));
        //cout << i << " " << dist[i] << '\n';
    }
    //cout << '\n';
    for (int i = 0; i < N; i++) {
        cout << i << " " << dist[i] << '\n';
    }
    while (Q--) {
        char c;
        cin >> c;
        if (c == 'Q') {
            int i, j;
            cin >> i >> j;
            cout << dist[j] - dist[i] << '\n';
        } else {
            int ind, x, y;
            cin >> ind >> x >> y;
            ind--;
            if (ind == 0) {
                for (int j = 2; j <= N; j++) {
                    dist[j] += vec[1].dist({x, y}) - dist[2];
                }
                vec[0] = {x, y};
            } else {
                //update ind + 1 ... N
                for (int i = ind + 1; i <= N; i++) {
                    dist[i] += vec[ind - 1].dist({x, y}) - vec[ind - 1].dist(vec[ind]);
                }
                for (int i = ind + 2; i <= N; i++) {
                    dist[i] += vec[ind + 1].dist({x, y}) - vec[ind + 1].dist(vec[ind]);
                }
                /*
                cout << endl;
                for (int j = 0; j <= N; j++) {
                    cout << j << " " << dist[j] << '\n';
                }
                cout << endl;
                 */
            }
        }
    }
}
