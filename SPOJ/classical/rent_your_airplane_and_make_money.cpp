#include <cmath>
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
using namespace std;
struct Event {
    int starting;
    int ending;
    int price;
    char c; //c = 'S' --> start
    //c = 'E' --> end
};
bool comp (Event e1, Event e2) {
    int time1, time2;
    if (e1.c == 'S') {
        time1 = e1.starting;
    } else {
        time1 = e1.ending;
    }
    if (e2.c == 'S') {
        time2 = e2.starting;
    } else {
        time2 = e2.ending;
    }
    return (time1 < time2);
}
void solve() {
    int n;
    cin >> n;
    vector<Event> vec;
    for (int i = 0; i < n; i++) {
        int x, y, z;
        cin >> x >> y >> z;
        vec.push_back({x, x + y, z, 'S'});
        vec.push_back({x, x + y, z, 'E'});
    }
    sort(vec.begin(), vec.end(), comp);
    set<int> s;
    map<int,int> re_index;
    for (int i = 0; i < vec.size(); i++) {
        s.insert(vec[i].ending);
        s.insert(vec[i].starting);
    }
    int cntr = 0;
    for (int i: s) {
        re_index[i] = ++cntr;
    }
    for (int i = 0; i < vec.size(); i++) {
        vec[i].starting = re_index[vec[i].starting];
        vec[i].ending = re_index[vec[i].ending];
    }
    vector<int> dp(2 * vec.size() + 2);
    for (int i = 0; i < dp.size(); i++) {
        dp[i] = 0;
    }
    int myMax = 0;
    for (int i = 0; i < vec.size(); i++) {
        if (vec[i].c == 'S') {
            dp[vec[i].starting] = max(dp[vec[i].starting - 1], dp[vec[i].starting]);
        } else {
            dp[vec[i].ending] = max(dp[vec[i].ending], dp[vec[i].ending - 1]);
            dp[vec[i].ending] = max(dp[vec[i].ending], dp[vec[i].starting] + vec[i].price);
            myMax = max(myMax, dp[vec[i].ending]);
        }
    }
    cout << myMax << endl;
}
int main() {
    int t;
    cin >> t;
    while(t--) {
        solve();
    }
}
