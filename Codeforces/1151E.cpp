#include <iostream>
#include <cmath>
#include <vector>
#include <set>
#include <chrono>
#include <random>
#include <queue>
#include <cstdint>
#include <cassert>
#include <bitset>
#include <map>
#include <list>
#include <stack>
#include <algorithm>

typedef long long ll;
using namespace std;
struct dsu{
    vector<int> parent;
    vector<int> compSize;
    int n;
    void fill(){
        parent.resize(n), compSize.resize(n);
        for(int i = 0; i < n; i++){
            parent[i] = i, compSize[i] = 1;
        }
    }
    int find_head(int x){
        if(x == parent[x]){
            return x;
        }
        return find_head(parent[x]);
    }
    void join(int x, int y){
        x = find_head(x);
        y = find_head(y);
        if(x == y){
            return;
        }
        if(compSize[x] > compSize[y]){
            swap(x,y);
            //ensures that compSize[x1] <= compSize[y1]
        }
        parent[x] = y;
        compSize[y] += compSize[x];
    }
    bool comp(int x, int y){
        return (find_head(x) == find_head(y));
    }
};
vector<int> a;
int n;

int f(int l, int r) {
    vector<bool> v;
    v.assign(n, false);
    for (int i = 0; i < a.size(); i++) {
        v[i] = (a[i] >= l && a[i] <= r);
    }
    vector<pair<int,int>> vec;
    for (int i = 0; i < v.size(); i++) {
        if (v[i] && (i != 0 && v[i - 1])) {
            vec.back().second++;
        } else if (v[i]) {
            vec.emplace_back(i, i);
        }
    }
    return vec.size();
}

ll ans = 0;

void print(vector<int> v) {
    int sum = 0;
    for (int i: v) {
        sum += i;
        //cout << i << " ";
    }
    //cout << '\n';
    cout << sum << '\n';
    ans += sum;
}

int main() {
    dsu d;
    cin >> n;
    int prev = -1;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        if (x == prev) {
            continue;
        }
        prev = x;
        a.push_back(x);
    }
    map<int,vector<int>> oc;
    for (int i = 0; i < a.size(); i++) {
        oc[a[i]].push_back(i);
    }
    ll cur = 0;
    vector<int> start(n);
    start[0] = oc[1].size();
    for (int i = 2; i <= n; i++) {
        start[i - 1] = start[i - 2];
        for (int j: oc[i]) {
            int left = n + 1;
            int right = n + 1;
            if (j != 0) {
                left = a[j - 1];
            }
            if (j != a.size() -1 ) {
                right = a[j + 1];
            }
            if (left < i && right < i) {
                start[i - 1]--;
            } else if (left > i && right > i) {
                start[i - 1]++;
            }
        }
        //start.push_back(f(1, i));
    }
    for (int i: start) {
        cur += i;
        //cout << i << ' ';
    }
    //return 0;
    ans += cur;
    //cout << ans << '\n';
    //print(start);
    for (int i = 2; i <= n; i++) {
        //i - 1 gets removed
        for (int j: oc[i - 1]) {
            int left = -1;
            int right = -1;
            if (j != 0) {
                left = a[j - 1];
            }
            if (j != a.size() -1 ) {
                right = a[j + 1];
            }
            if (left < i - 1 && right < i - 1) {
                cur -= max((n - 1) - (i - 2) + 1, 0);
                /*
                for (int ind = i - 2; ind < n; ind++) {
                    start[ind]--;
                }
                 */
            } else if (left > i - 1 && right > i - 1) {
                cur -= max(min(left, right) - i + 1, 0);
                /*
                for (int ind = i - 2; ind <= min(left, right) - 2; ind++) {
                    start[ind]--;
                }
                 */
                cur += max((n - 1) - (max(left, right) - 1) + 1, 0);
                /*
                for (int ind = max(left, right) - 1; ind < n; ind++) {
                    start[ind]++;
                }
                 */
            } else {
                cur -= max(max(left, right) - i + 1, 0);
                /*
                for (int ind = i - 2; ind < max(left, right) - 1; ind++) {
                    start[ind]--;
                }
                 */
            }
            //cout << cur << '\n';
            //ans += cur;
        }
        ans += cur;
    }
    cout << ans << '\n';
}
