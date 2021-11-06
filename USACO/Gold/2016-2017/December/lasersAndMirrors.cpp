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
struct Node {
    int dirx, diry;
    int locx, locy;
    int cost;
};
int main() {
    freopen("lasers.in", "r", stdin);
    freopen("lasers.out", "w", stdout);
    map<int,set<int>> x, y;
    int N;
    cin >> N;
    vector<pair<int,int>> vec;
    for (int i = 0; i < N + 2; i++) {
        int a, b;
        cin >> a >> b;
        vec.push_back({a, b});
        x[a].insert(b), y[b].insert(a);
    }
    deque<Node> q;
    map<pair<pair<int,int>,pair<int,int>>,int> myMap;
    q.push_back({0, 1, vec[0].first, vec[0].second, 0});
    q.push_back({0, -1, vec[0].first, vec[0].second, 0});
    q.push_back({1, 0, vec[0].first, vec[0].second, 0});
    q.push_back({-1, 0, vec[0].first, vec[0].second, 0});
    while (!q.empty()) {
        Node cur = q.front();
        q.pop_front();
        if (myMap[{{cur.locx, cur.locy}, {cur.dirx, cur.diry}}]) {
            continue;
        }
        myMap[{{cur.locx, cur.locy}, {cur.dirx, cur.diry}}] = true;
        if (cur.locx == vec[1].first && cur.locy == vec[1].second) {
            cout << cur.cost;
            return 0;
        }
        pair<int,int> nxt;
        auto itx = x[cur.locx].find(cur.locy);
        auto ity = y[cur.locy].find(cur.locx);
        if (cur.dirx < 0) {
            if (ity == y[cur.locy].begin()) {
                nxt = {-1, -1};
            } else {
                ity--;
            }
        } else if (cur.diry < 0) {
            if (itx == x[cur.locx].begin()) {
                nxt = {-1, -1};
            } else {
                itx--;
            }
        } else if (cur.dirx > 0) {
            ity++;
            if (ity == y[cur.locy].end()) {
                nxt = {-1, -1};
            }
        } else {
            itx++;
            if (itx == x[cur.locx].end()) {
                nxt = {-1, -1};
            }
        }
        if (nxt.first != -1) {
            nxt = {*ity, *itx};
        }
        if (nxt.first != -1) q.push_front({cur.dirx, cur.diry, nxt.first, nxt.second, cur.cost});
        q.push_back({cur.diry, cur.dirx, cur.locx, cur.locy, cur.cost + 1});
        q.push_back({-cur.diry, -cur.dirx, cur.locx, cur.locy, cur.cost + 1});
    }
    cout << "-1\n";
}
