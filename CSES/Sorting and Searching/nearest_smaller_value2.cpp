#include <vector>
#include <iostream>
#include <cassert>
#include <cmath>
#include <set>
#include <map>
#include <stack>
#include <set>
#define ll int
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    vector<pair<int,int>> myStack; //location, value
    for (int i = 0; i < n; i++) {
        while (!myStack.empty() && arr[i] <= myStack.back().second) {
            myStack.pop_back();
        }
        if (myStack.empty()) {
            cout << 0 << " ";
        } else {
            cout << myStack.back().first + 1 << ' ';
        }
        myStack.push_back({i, arr[i]});
    }
}
