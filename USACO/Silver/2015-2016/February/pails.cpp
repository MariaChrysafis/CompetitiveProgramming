#include <vector>
#include <iostream>
#include <cassert>
#include <cmath>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <climits>
#include <unordered_map>
#include <set>
#include <algorithm>
#include <iomanip>

using namespace std;
int X, Y;
struct State {
    int x, y, dist;
};
State empty1 (State s) {
    s.dist++, s.x = 0;
    return s;
}
State empty2 (State s) {
    s.dist++, s.y = 0;
    return s;
}
State fill1 (State s) {
    s.dist++, s.x = X;
    return s;
}
State fill2 (State s) {
    s.dist++, s.y = Y;
    return s;
}
State swap1 (State s) {
    s.dist++;
    State new_s = s;
    new_s.x = s.x - min(s.x, Y - s.y), new_s.y = s.x + s.y - new_s.x;
    return new_s;
}
State swap2 (State s) {
    s.dist++;
    State new_s = s;
    new_s.y = s.y - min(s.y, X - s.x), new_s.x = s.x + s.y - new_s.y;
    return new_s;
}
int main() {
    freopen("pails.in", "r", stdin);
    freopen("pails.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int K, M;
    cin >> X >> Y;
    cin >> K >> M;
    queue<State> q;
    q.push({0, 0});
    bool hasVisited[X + 1][Y + 1];
    for (int i = 0; i <= X; i++) {
        for (int j = 0; j <= Y; j++) {
            hasVisited[i][j] = false;
        }
    }
    int myMin = (int)1e9;
    while (!q.empty()) {
        State s = q.front();
        q.pop();
        if (hasVisited[s.x][s.y]) {
            continue;
        }
        if (s.dist > K) {
            break;
        }
        myMin = min(myMin, abs(s.x + s.y - M));
        hasVisited[s.x][s.y] = true;
        q.push(swap1(s));
        q.push(swap2(s));
        q.push(empty1(s));
        q.push(empty2(s));
        q.push(fill1(s));
        q.push(fill2(s));
    }
    cout << myMin;
}
