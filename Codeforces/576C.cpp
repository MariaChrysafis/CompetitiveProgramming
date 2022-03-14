#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <cmath>
#include <cassert>
#include <map>
#include <random>
#include <ctime>
#include <random>
#include <cstdlib>

using namespace std;
int64_t distance (pair<int,int> p, pair<int,int> q) {
    return abs(p.first - q.first) + abs(p.second - q.second);
}
bool okay (vector<pair<pair<int,int>,int>> vec) {
    int64_t ans = 0;
    for (int i = 1; i < vec.size(); i++) {
        ans += distance(vec[i].first, vec[i - 1].first);
    }
    return (ans < 2500000000);
}
bool comp (pair<pair<int,int>,int> p1, pair<pair<int,int>,int> p2) {
    return make_pair(make_pair(p1.first.first/1000,p1.first.second/1000),p1.first) < make_pair(make_pair(p2.first.first/1000,p2.first.second/1000), p2.first);
}
bool comp1 (pair<pair<int,int>,int> p1, pair<pair<int,int>,int> p2) {
    return make_pair(p1.first.first/900,p1.first.second/900) < make_pair(p2.first.first/900,p2.first.second/900);
}
void print (vector<pair<pair<int,int>,int>> vec) {
    if (okay(vec)) {
        for (auto& p: vec) {
            cout << p.second + 1 << ' ';
        }
        exit(0);
    }
    return;
}
int main() {
    srand(time(NULL));
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N; cin >> N;
    vector<pair<pair<int,int>,int>> vec(N);
    for (int i = 0; i < N; i++) {
        cin >> vec[i].first.first >> vec[i].first.second;
        vec[i].second = i;
    }
    sort(vec.begin(), vec.end(), comp);
    print(vec);
    random_shuffle(vec.begin(), vec.end());
    sort(vec.begin(), vec.end(), comp1);
    print(vec);
}
