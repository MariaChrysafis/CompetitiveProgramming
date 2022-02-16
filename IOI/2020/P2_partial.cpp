#include <cmath>
#include <cassert>
#include <iostream>
#include <set>
#include <climits>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <type_traits>
#include <string>
#include <queue>
#include <map>
#include "supertrees.h"
 
#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("Ofast")
#pragma GCC optimization ("unroll-loops")
 
using namespace std;
 
class DisjointSetUnion {
protected:
    vector<int> parent;
    vector<int> compSize;
    const int n;
    int connectedComponents;
public:
    int getConnectedComponents() const {
        return connectedComponents;
    }
 
public:
    DisjointSetUnion(int sz) : n(sz), connectedComponents(sz) {
        parent.resize(sz), compSize.resize(sz);
        for (int i = 0; i < n; i++) {
            parent[i] = i, compSize[i] = 1;
        }
    }
 
    int find_head(int x) const {
        int cur = x;
        while (cur != parent[cur]) {
            cur = parent[cur];
        }
        return cur;
    }
 
    void join(int x, int y) {
        x = find_head(x);
        y = find_head(y);
        if (x == y) {
            return;
        }
        if (compSize[x] > compSize[y]) {
            swap(x, y);
            //ensures that compSize[x1] <= compSize[y1]
        }
        parent[x] = y;
        compSize[y] += compSize[x];
        connectedComponents--;
    }
 
    bool comp(int x, int y) {
        return (find_head(x) == find_head(y));
    }
};
 
 
/*
void build (vector<vector<int>> grid) {
    for (int i = 0; i < grid.size(); i++) {
        for (int j: grid[i]) {
            cout << j << ' ';
        }
        cout << '\n';
    }
}
 
*/
 
 
 
int construct (vector<vector<int>> grid) {
    vector<vector<int>> ans(grid.size());
    for (int i = 0; i < grid.size(); i++) {
        ans[i].assign(grid[0].size(), 0);
    }
    set<int> s;
    map<int,int> cnt;
    DisjointSetUnion disjointSetUnion(grid.size());
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid.size(); j++) {
            s.insert(grid[i][j]);
            cnt[grid[i][j]]++;
            if (grid[i][j] != 0) {
                disjointSetUnion.join(i, j);
            }
        }
    }
    if (s.count(1) && s.size() == 1) {
        for (int i = 1; i < grid.size(); i++) {
            ans[i][0] = ans[0][i] = 1;
        }
        build(ans);
        return 1;
    }
    map<int,vector<int>> myMap;
    for (int i = 0; i < grid.size(); i++) {
        myMap[disjointSetUnion.find_head(i)].push_back(i);
    }
    if (cnt[2] == 0 && cnt[3] == 0) {
        for (auto& p: myMap) {
            vector<int> v = p.second;
            for (int i = 1; i < (int)v.size(); i++) {
                ans[v[i]][v[0]] = 1;
                ans[v[0]][v[i]] = 1;
            }
            for (int x: v) {
                for (int y: v) {
                    if (grid[x][y] != 1) return false;
                }
            }
        }
        build(ans);
        return 1;
    }
    if (cnt[0] >= 0 && cnt[1] == (int)grid.size() && cnt[2] >= 0 && cnt[3] == 0) {
        for (auto& p: myMap) {
            vector<int> v = p.second;
            if (v.size() == 2) {
                return 0;
            }
            if (v.size() <= 1) {
                continue;
            }
            for (int i = 1; i < (int)v.size(); i++) {
                ans[v[i]][v[i - 1]] = 1;
                ans[v[i - 1]][v[i]] = 1;
            }
            ans[v[0]][v.back()] = ans[v.back()][v[0]] = 1;
            for (int x: v) {
                for (int y: v) {
                    if (grid[x][y] == 0) {
                        return 0;
                    }
                }
            }
        }
        build(ans);
        return 1;
    }
}
 
/*
int main () {
    const int N = 7;
    vector<vector<int>> grid(N);
    for (int i = 0; i < N; i++) {
        grid[i].assign(N, 0);
        grid[i][i] = 1;
    }
    grid[1][2] = grid[2][1] = 2;
    grid[1][3] = grid[3][1] = 2;
    grid[2][3] = grid[3][2] = 2;
 
    grid[3][5] = grid[5][3] = 2;
    grid[3][6] = grid[6][3] = 2;
    grid[5][6] = grid[6][5] = 2;
    construct(grid);
}
 */
