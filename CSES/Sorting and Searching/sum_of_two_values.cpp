#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <cmath>
#include <map>
 
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N, X;
    cin >> N >> X;
    map<int,int> myMap;
    for (int i = 0; i < N; i++) {
        int x;
        cin >> x;
        if (myMap.count(X - x)) {
            cout << myMap[X - x] + 1 << " " << i + 1 << '\n';
            exit(0);
        }
        myMap[x] = i;
    }
    cout << "IMPOSSIBLE\n";
}
