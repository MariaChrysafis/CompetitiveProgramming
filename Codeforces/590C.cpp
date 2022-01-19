#include <vector>
#include <chrono>
#include <iostream>
#include <map>
#include <set>
#include <climits>
#include <cmath>
#include <cassert>
#include <iomanip>
#include <stack>
#include <unordered_map>
#include <queue>
#include <algorithm>
#include <string>

using namespace std;

typedef int64_t ll;
vector<string> grid;

struct Query {
    int distance;
    int x;
    int y;
};

const int INF = 1e8;

vector<vector<int>> enque (char c) {
    deque<Query> myQueue;
    bool hasVisited[grid.size()][grid[0].size()];
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[0].size(); j++) {
            if (grid[i][j] == c) {
                myQueue.push_back({0, i, j});
            }
            hasVisited[i][j] = false;
        }
    }
    vector<vector<int>> dist(grid.size());
    for (int i = 0; i < grid.size(); i++) {
        dist[i].resize(grid[0].size());
        for (int j = 0; j < grid[0].size(); j++) {
            dist[i][j] = INF;
        }
    }
    while (!myQueue.empty()) {
        Query cur = myQueue.front();
        //cout << cur.x << " " << cur.y << " " << cur.distance << '\n';
        myQueue.pop_front();
        if (hasVisited[cur.x][cur.y]) {
            continue;
        }
        hasVisited[cur.x][cur.y] = true;
        dist[cur.x][cur.y] = cur.distance;
        for (int dx = -1; dx <= 1; dx++) {
            for (int dy = -1; dy <= 1; dy++) {
                if (cur.x + dx < 0 || cur.x + dx == grid.size() || cur.y + dy < 0 || cur.y + dy == grid[0].size() || abs(dx) + abs(dy) != 1) {
                    continue;
                }
                if (grid[cur.x + dx][cur.y + dy] == '.') {
                    myQueue.push_back({cur.distance + 1, cur.x + dx, cur.y + dy});
                } else if (grid[cur.x + dx][cur.y + dy] <= '3' && grid[cur.x + dx][cur.y + dy] >= '1'){
                    myQueue.push_front({cur.distance, cur.x + dx, cur.y + dy});
                }
            }
        }
    }
    return dist;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N, M;
    cin >> N >> M;
    grid.resize(N);
    for (int i = 0; i < N; i++) {
        cin >> grid[i];
    }
    vector<vector<int>> dist[3];
    dist[0] = enque('1');
    dist[1] = enque('2');
    dist[2] = enque('3');
    int myMin = INF;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            int myDist = dist[0][i][j] + dist[1][i][j] + dist[2][i][j];
            //cout << i << " " << j << ": " << dist[0][i][j] << " " << dist[1][i][j] << " " << dist[2][i][j] << '\n';
            myDist -= 2 * (grid[i][j] == '.');
            //cout << i << " " << j << ": " << myDist << '\n';
            myMin = min(myMin, myDist);
        }
    }
    if (myMin == INF) {
        cout << "-1\n";
        return 0;
    }
    cout << myMin;
}
