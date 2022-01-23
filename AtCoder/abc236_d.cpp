#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <map>
#include <algorithm>
#include <set>
#include <queue>
#include <stack>
#include <list>
#include <cstring>

using namespace std;
typedef long long ll;
void print (vector<int> v) {
    for (int i: v) {
        cout << i << ' ';
    }
    cout << '\n';
}
vector<vector<int>> arr;
void push_front (vector<int>&v) {
    reverse(v.begin(), v.end());
    v.push_back(-1);
    reverse(v.begin(), v.end());
}
int myMax = 0;
void rec (vector<bool> hasVisited, int bxor) {
    int st = -1;
    for (int i = 0; i < hasVisited.size(); i++) {
        if (!hasVisited[i]) {
            st = i;
        }
    }
    if (st == -1) {
        //cout << bxor << '\n';
        myMax = max(myMax, bxor);
        return;
    }
    for (int i = 0; i < arr.size(); i++) {
        if (arr[st][i] != -1 && !hasVisited[i]) {
            hasVisited[i] = true, hasVisited[st] = true;
            rec(hasVisited, bxor ^ arr[st][i]);
            hasVisited[i] = false, hasVisited[st] = false;
        }
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    arr.resize(2 * n);
    for (int i = 0; i < 2 * n; i++) {
        arr[i].resize(2 * n - i - 1);
        for (int j = 0; j < arr[i].size(); j++) {
            cin >> arr[i][j];
        }
        int t = i + 1;
        while (t--) {
            push_front(arr[i]);
        }
        //print(arr[i]);
    }
    for (int i = 0; i < arr.size(); i++) {
        for (int j = 0; j < arr.size(); j++) {
            if (i == j) {
                continue;
            }
            arr[i][j] = max(arr[j][i], arr[i][j]);
            arr[j][i] = max(arr[i][j], arr[j][i]);
        }
    }
    vector<bool> hv;
    hv.assign(2 * n, false);
    rec(hv, 0);
    cout << myMax;
}
