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
vector<int> remove (vector<int> v, int x) {
    vector<int> vec;
    for (int i = 0; i < v.size(); i++) {
        if (v[i] != x) {
            vec.push_back(v[i]);
        }
    }
    return vec;
}
bool smaller (vector<int> v, vector<int> v1) {
    for (int i = 0; i < min(v.size(), v1.size()); i++) {
        if(v[i] < v1[i]) {
            return true;
        } else if (v[i] > v1[i]) {
            return false;
        }
    }
    return (v.size() < v1.size());
}
void print (vector<int> v) {
    for (int i: v) cout << i << ' ';
    cout << '\n';
}
int main() {
    int n;
    cin >> n;
    vector<int> arr(n);
    int myMax = 0;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        myMax = max(myMax, arr[i]);
    }
    for (int i = 1; i < n; i++) {
        if (arr[i] < arr[i - 1]) {
            print(remove(arr, arr[i - 1]));
            return 0;
        }
    }
    print(remove(arr, myMax));

}
