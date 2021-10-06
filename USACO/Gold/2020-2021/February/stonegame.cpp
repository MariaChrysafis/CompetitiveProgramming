#include <iostream>
#include <vector>
#include <cassert>
#include <map>
#include <set>
#include <chrono>

#include <queue>
#include <algorithm>
#include <cmath>
#include <fstream>

#pragma GCC optimize("O3")
using namespace std;

int vec_max(vector<int> v) {
    int myMax = 0;
    for (int i: v) {
        myMax = max(myMax, i);
    }
    return myMax;
}
int main() {
    int n;
    cin >> n;
    vector<int> v(n);
    int pref[(int)3e6 + 10];
    int oc[(int)3e6 + 10];
    for (int i = 0; i < n; i++) {
        cin >> v[i];
        oc[v[i]]++;
    }
    pref[0] = 0;
    for (int i = 1; i < (int)3e6; i++) {
        pref[i] = pref[i - 1] + oc[i - 1];
    }
    long long cntr = 0;
    int myMax = vec_max(v);
    for (int div = 1; div <= myMax; div++) {
        long long myMap[myMax/div + 1];
        vector<int> s;
        for (int i = 0; i <= myMax/div; i++) {
            int right;
            right = pref[div * (i + 1)];
            myMap[i] = right - pref[div * i];
            if(myMap[i] % 2 == 1) {
                s.push_back(i);
                if(s.size() > 2) {
                    break;
                }
            }
        }
        if(s.size() > 2) {
            continue;
        }
        for (int i: s) {
            if (i == 0) continue;
            myMap[i]--;
            myMap[i - 1]++;
            bool fine = true;
            for(int j = 1; j < myMax/div + 1; j++) {
                if(myMap[j] % 2 == 1) {
                    fine = false;
                    break;
                }
            }
            if(fine) {
                cntr += myMap[i] + 1;
            }
            myMap[i]++;
            myMap[i - 1]--;
        }
    }
    cout << cntr << endl;
}
