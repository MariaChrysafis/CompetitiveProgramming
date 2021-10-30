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
int main() {
    int n;
    cin >> n;
    map<int,int> myMap;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    reverse(arr.begin(), arr.end());
    for (int i = 0; i < n; i++) {
        myMap[arr[i]] = max(myMap[arr[i] + 1] + 1, myMap[arr[i]]);
    }
    int myMax = 0;
    int best = 0;
    for (auto p: myMap) {
        //cout << p.first << " " << p.second << '\n';
        if (p.second > myMax) {
            best = p.first;
            myMax = p.second;
        }
    }
    //cout << best << endl;
    reverse(arr.begin(), arr.end());
    vector<int> ans;
    for (int i = 0; i < arr.size(); i++) {
        if (arr[i] == best) {
            best++;
            ans.push_back(i + 1);
        }
    }
    cout << ans.size() << endl;
    for (int i: ans) {
        cout << i << " ";
    }
    cout << endl;
}
