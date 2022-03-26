#include <vector>
#include <algorithm>
#include <iostream>
#include <set>
#include <cmath>
#include <map>
#include <random>
#include <cassert>
#include <ctime>
#include <cstdlib>
#include <queue>
#include <limits.h>
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N, M; cin >> N >> M;
    vector<pair<int,int>> vec;
    for (int i = 0; i < M; i++) {
        int x, y;
        cin >> x >> y;
        x--, y--;
        vec.emplace_back(x, y);
    }
    int c = 0;
    for (int i = 0; i < (1 << N); i++) {
        bool fine = true;
        for (auto& p: vec) {
            if ((i & (1 << p.first)) && (i & (1 << p.second))) {
                fine = false;
                break;
            }
        }
        c += fine;
    }
    cout << c;
}
