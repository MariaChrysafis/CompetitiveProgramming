
#include <cmath>
#include <iostream>
#include <set>
#include <climits>
#include <algorithm>
#include <cassert>
#include <vector>
#include <iomanip>
#include <type_traits>
#include <string>
#include <queue>
#include <map>
using namespace std;
#define ll long long
struct item {
    long long weight;
    long long worth;
    long long cnt;
};
bool comp (item i1, item i2) {
    if (i1.weight == i2.weight) {
        return (i1.worth > i2.worth);
    }
    return (i1.weight < i2.weight);
}
int main() {
    //freopen("hamming.in", "r", stdin);
    long long S, N;
    cin >> S >> N;
    vector<item> items;
    for (int i = 0; i < N; i++) {
        long long wei, wor;
        cin >> wor >> wei;
        long long cnt;
        cin >> cnt;
        items.push_back({wei, wor, cnt});
    }
    sort(items.begin(), items.end(), comp);
    vector<item> new_item;
    map<int,int> myMap;
    for (item item: items) {
        if (myMap[item.weight] * item.weight > S) {
            continue;
        }
        myMap[item.weight] += item.cnt;
        new_item.push_back(item);
    }
    swap(new_item, items);
    long long dp[S + 1];
    for (int j = 0; j <= S; j++) {
        dp[j] = 0;
    }
    long long myMax = 0;
    for (int i = 1; i <= items.size(); i++) {
        for (int j = S; j >= 0; j--) {
            int cntr = 0;
            while (cntr * items[i - 1].weight <= j && cntr <= items[i - 1].cnt) {
                dp[j] = max(dp[j], dp[j - cntr * items[i - 1].weight] + cntr * items[i - 1].worth);
                cntr++;
            }
            myMax = max(myMax, dp[j]);
        }
    }
    cout << myMax << endl;
}
