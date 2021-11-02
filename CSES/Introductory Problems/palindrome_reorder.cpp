#include <vector>
#include <iostream>
#include <cassert>
#include <cmath>
#include <set>
#include <map>
#include <stack>
#include <set>
#include <algorithm>
#include <iomanip>
#define ll unsigned long long
using namespace std;
int dist (pair<int,int> p1, pair<int,int> p2) {
    return abs(p1.first - p2.first) + abs(p1.second - p2.second);
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string s;
    cin >> s;
    map<char,int> myMap;
    for (int i = 0; i < s.length(); i++) {
        myMap[s[i]]++;
    }
    int cntr = 0;
    char c;
    for (pair<char,int> p: myMap) {
        if (p.second % 2 == 1) {
            cntr++;
            c = p.first;
        }
    }
    if (cntr >= 2) {
        cout << "NO SOLUTION\n";
    } else {
        string front;
        for (pair<char,int> p: myMap) {
            p.second /= 2;
            while (p.second --) {
                front += p.first;
            }
        }
        if (cntr == 1) {
            cout << front << c;
            reverse(front.begin(), front.end());
            cout << front;
        } else {
            cout << front;
            reverse(front.begin(), front.end());
            cout << front;
        }
    }
}
