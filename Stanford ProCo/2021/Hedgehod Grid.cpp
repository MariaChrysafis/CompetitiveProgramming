#include <iostream>
#include <queue>
#include <climits>
#include <map>
using namespace std;
struct Location {
    int x;
    int y;
    int speed;
    int direction;
    int dist;
    Location (int x, int y, int speed, int dir, int dist) {
        this->x = x, this-> y = y, this->speed = speed, this->direction = dir, this->dist = dist;
    }
};
string arr[400];
int dir[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
int N, M;
bool okay (int x1, int y1, int delta, pair<int,int> p) {
    if (x1 < 0 || x1 < 0 || x1 >= N || y1 >= M) return false;
    if (delta == 0) {
        return (arr[x1][y1] == '0');
    }
    return (arr[x1][y1] == '0' && okay(x1 + p.first, y1 + p.second, delta - 1, p));
}
int main() {
    cin >> N >> M;
    for (int i = 0; i < N; i++) {
        cin >> arr[i];
    }
    map<int,int> dp[N][M][4];
    queue<Location> q;
    q.push(Location(0, 0, 0, 2, 0));
    while (!q.empty()) {
        auto p = q.front();
        q.pop();
        if (p.speed > 400) {
            continue;
        }
        if (p.x == N - 1 && p.y == M - 1) {
            cout << p.dist;
            exit(0);
        }
        if (p.x < 0 || p.y < 0 || p.x >= N || p.y >= M) {
            continue;
        }
        if (arr[p.x][p.y] == '1') {
            continue;
        }
        if (dp[p.x][p.y][p.direction].count(p.speed)) {
            continue;
        }
        dp[p.x][p.y][p.direction][p.speed] = p.dist;
        if (okay(p.x, p.y, p.speed + 1, {dir[p.direction][0], dir[p.direction][1]})) {
            q.push(Location(p.x + (p.speed + 1) * dir[p.direction][0], p.y + (p.speed + 1) * dir[p.direction][1], p.speed + 1, p.direction, p.dist + 1));
        }
        if (okay(p.x, p.y, p.speed - 1, {dir[p.direction][0], dir[p.direction][1]})) {
            q.push(Location(p.x + (p.speed - 1) * dir[p.direction][0], p.y + (p.speed - 1) * dir[p.direction][1], p.speed - 1, p.direction, p.dist + 1));
        }
        if (p.speed == 0) {
            for (int j = 0; j < 4; j++) {
                q.push(Location(p.x, p.y, p.speed, j, p.dist + 1));
            }
        }
    }
}
