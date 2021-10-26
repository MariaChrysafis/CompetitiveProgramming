#include <cmath>
#include <iostream>
#include <set>
#include <climits>
#include <algorithm>
#include <cassert>
#include <vector>
#include <iomanip>
#include <type_traits>
#include <string>
#include <queue>
#include <map>
using namespace std;
#define ll int
int N, A, B;
vector<string> vec;
int bfs (int x, int y) {
    priority_queue<pair<int,pair<int,int>>> pq; //priority queue for the distances
    int dist[N][N];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            dist[i][j] = -1;
        }
    }
    pq.push({0, {x, y}});
    int myMax = 0;
    while (!pq.empty()) {
        int distance = pq.top().first;
        pair<int,int> cur = pq.top().second;
        pq.pop();
        if (dist[cur.first][cur.second] != -1) {
            continue;
        }
        dist[cur.first][cur.second] = -distance;
        myMax = max(myMax, -distance);
        for (int dx = -1; dx <= 1; dx++) {
            for (int dy = -1; dy <= 1; dy++) {
                //cout << "YES\n";
                if (abs(dx) + abs(dy) != 1) continue;
                if (cur.first + dx < 0 || cur.second + dy < 0) continue;
                if (cur.first + dx == N || cur.second + dy == N) continue;
                int penalty = (vec[cur.first + dx][cur.second + dy] == vec[cur.first][cur.second]);
                if (penalty == 1) penalty = A;
                else penalty = B;
                pair<int,int> nxt = {cur.first + dx, cur.second + dy};
                pq.push(make_pair(distance - penalty, nxt));
            }
        }
    }
    return myMax;
}
int main() {
    freopen("distant.in", "r", stdin);
    freopen("distant.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> N >> A >> B;
    vec.resize(N);
    for (int i = 0; i < N; i++) {
        cin >> vec[i];
    }
    int myMax = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            myMax = max(myMax, bfs(i, j));
        }
    }
    cout << myMax;
}
