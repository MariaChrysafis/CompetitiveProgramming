/*
 * 8 2 12
1 2 4 2 1 3 5 6 2 3 6 4
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <cmath>
#include <iomanip>
#include <map>
#include <queue>
#include <set>
using namespace std;
void print(vector<int> v) {
    for (int i: v) {
        cout << i << " ";
    }
    cout << endl;
}
/*
vector<int> vec = {1, 2, 1, 3, 2, 2, 2, 3, 4, 5, 4};
int query(vector<int> sub) {
    set<int> s;
    for (int i: sub) {
        s.insert(vec[i]);
    }
    return s.size();
}
 */
int query(vector<int> v) {
    if (v.size() == 0) {
        return 0;
    }
    cout << v.size();
    for (int i: v) {
        cout << " " << i + 1;
    }
    cout << endl;
    int ans;
    cin >> ans;
    return ans;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    vector<int> sub;
    vector<int> ans;
    map<int,int> myMap;
    int cur = 0;
    for (int i = 0; i < n; i++) {
        sub.push_back(i);
        int x = query(sub);
        if (x == cur + 1) {
            ans.push_back(cur + 1);
            myMap[cur + 1] = ans.size() - 1;
            cur++;
        } else {
            int l = 1; 
            int r = cur;
            while (l < r) {
                int m = (l + r)/2;
                vector<int> q1, q2;
                for (int j = 1; j <= m; j++) {
                    q1.push_back(myMap[j]);
                }
                q2 = q1;
                q2.push_back(i);
                if (query(q1) == query(q2)) {
                    r = m;
                } else {
                    l = m + 1;
                }
            }
            ans.push_back(l);
        }
    }
    cout << "0 ";
    print(ans);
}
