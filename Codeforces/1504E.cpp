#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <cmath>
#include <set>
#include <queue>
 
#define ll long long
using namespace std;
#define P(x, y) make_pair(x,y)
using namespace std;
void print(vector<int> v){
    for(int i: v) cout << i << " ";
    cout << endl;
}
int main() {
    int n;
    cin >> n;
    vector<pair<long long, long long>> v(n);
    long long cost = 0;
    for(int i = 0; i < n; i++) {
        cin >> v[i].first >> v[i].second;
        cost += v[i].second;
    }
    sort(v.begin(), v.end());
    vector<int> added;
    long long curMax = -1;
    for(int i = 0; i < v.size(); i++){
        if(v[i].first + v[i].second > curMax){
            curMax = v[i].first + v[i].second;
            added.push_back(i);
        }
    }
    if(added.back() != n - 1){
        added.push_back(n - 1);
    }
    for(int i = 0; i < added.size() - 1; i++){
        cost += max(0ll, v[added[i + 1]].first - v[added[i]].first - v[added[i]].second);
    }
    cout << cost << endl;
}
