#include <iostream>
#include <cmath>
#include <vector>
#include <set>
#include <chrono>
#include <random>
#include <queue>
#include <cassert>
#include <map>
#include <algorithm>

#define ll long long
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll vladik, valera;
    cin >> vladik >> valera;
    int candies = 1;
    while (true) {
        if (candies % 2 == 1) {
            if (vladik - candies >= 0) {
                vladik -= candies;
                //valera += candies;
            } else {
                cout << "Vladik\n";
                return 0;
            }
        } else {
            if (valera - candies >= 0) {
                //vladik += candies;
                valera -= candies;
            } else {
                cout << "Valera\n";
                return 0;
            }
        }
        candies++;
        //cout << candies << '\n';
    }
}
