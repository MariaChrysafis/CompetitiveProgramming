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
vector<int> powr;
int swap (int x, int pos1, int pos2) {
    int dif = x/powr[pos1] % 9 - x / powr[pos2] % 9;
    x += -powr[pos1] * dif + powr[pos2] * dif;
    return x;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    powr = {1};
    while (powr.size() != 9) {
        powr.push_back(powr.back() * 9);
    }
    int orig = 0;
    int des = 0;
    for (int i = 0; i < 9; i++) {
        int x;
        cin >> x;
        x--;
        orig += powr[i] * x;
        des += powr[i] * i;
    }
    queue<pair<int, int>> q;
    q.push(make_pair(orig, 0));
    vector<bool> hasVisited(387420489);
    while (!q.empty()) {
        int dist = q.front().second;
        int grid = q.front().first;
        q.pop();
        if (grid == des) {
            cout << dist;
            return 0;
        }
        if (hasVisited[grid]) {
            continue;
        }
        hasVisited[grid] = true;
        for (int i = 0; i < 6; i++) {
            grid = swap(grid, i, i + 3);
            q.push(make_pair(grid, dist + 1));
            grid = swap(grid, i, i + 3);
        }
        for (int i = 0; i < 9; i++) {
            if (i % 3 == 2) {
                continue;
            }
            grid = swap(grid, i, i + 1);
            q.push(make_pair(grid, dist + 1));
            grid = swap(grid, i, i + 1);
        }
    }
}
