#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <cmath>

using namespace std;
vector<int> a;
vector<bool> hasVisited;
int cnt = 0;
bool comp (pair<pair<int,int>,int> p1, pair<pair<int,int>,int> p2) {
    p1.first.first /= 1000;
    p2.first.first /= 1000;
    return (p1 < p2);
}
void update (int x) {
    cnt -= hasVisited[a[x]];
    hasVisited[a[x]] = !hasVisited[a[x]];
    cnt += hasVisited[a[x]];
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N;
    cin >> N;
    a.resize(N);
    hasVisited.assign(N, false);
    for (int i = 0; i < N; i++) {
        cin >> a[i];
    }
    int Q;
    cin >> Q;
    vector<pair<pair<int,int>,int>> vec;
    for (int q = 0; q < Q; q++) {
        int l, r;
        cin >> l >> r;
        l--, r--;
        vec.push_back({{l, r}, q});
    }
    sort(vec.begin(), vec.end(), comp);
    int l = 0;
    int r = -1;
    int ans[Q];
    for (int i = 0; i < vec.size(); i++) {
        while (l < vec[i].first.first) {
            update(l++);
        }
        while (l > vec[i].first.first) {
            update(--l);
        }
        while (r < vec[i].first.second) {
            update(++r);
        }
        while (r > vec[i].first.second) {
            update(r--);
        }
        ans[vec[i].second] = (vec[i].first.second - vec[i].first.first + 1 - cnt)/2;
    }
    for (int i: ans) {
        cout << i << '\n';
    }
}
