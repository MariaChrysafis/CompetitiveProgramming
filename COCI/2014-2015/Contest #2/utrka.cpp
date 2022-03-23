#include <vector>
#include <algorithm>
#include <iostream>
#include <set>
#include <cmath>
#include <map>
#include <random>
#include <cassert>
#include <ctime>
#include <cstdlib>
#include <limits.h>
 
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N; cin >> N;
    map<string,int> myMap;
    for (int i = 0; i < N; i++) {
        string x; cin >> x;
        myMap[x]++;
    }
    for (int i = 0; i < N - 1; i++) {
        string x; cin >> x;
        myMap[x]--;
    }
    //cout << *(s.begin());
    for (auto& p: myMap) {
        if (p.second == 1) {
            cout << p.first;
            exit(0);
        }
    }
}
