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
    int N = 9;
    vector<int> v(N);
    map<int,string> oc;
    for (int i = 0; i < N; i++) {
        cin >> v[i];
        oc[v[i]] = to_string(i + 1);
    }
    string s;
    cin >> s;
    vector<char> vec;
    string prev = "?";
    string cur;
    for (int i = 0; i < s.length(); i++) {
        cur = "";
        if (s[i] >= 'a' && s[i] <= 'c') {
            while (s[i] >= 'a' && s[i] <= 'c') {
                cur += oc[2];
                s[i]--;
            }
            if (cur.back() == prev.back()) {
                cout << '#';
            }
            cout << cur;
            prev = cur;
            continue;
        }
        if (s[i] >= 'd' && s[i] <= 'f') {
            while (s[i] >= 'd' && s[i] <= 'f') {
                cur += oc[3];
                s[i]--;
            }
            if (cur.back() == prev.back()) {
                cout << '#';
            }
            cout << cur;
            prev = cur;
            continue;
        }
        if (s[i] >= 'g' && s[i] <= 'i') {
            while (s[i] >= 'g' && s[i] <= 'i') {
                cur += oc[4];
                s[i]--;
            }
            if (cur.back() == prev.back()) {
                cout << '#';
            }
            cout << cur;
            prev = cur;
            continue;
        }
        if (s[i] >= 'j' && s[i] <= 'l') {
            while (s[i] >= 'j' && s[i] <= 'l') {
                cur += oc[5];
                s[i]--;
            }
            if (cur.back() == prev.back()) {
                cout << '#';
            }
            cout << cur;
            prev = cur;
            continue;
        }
        if (s[i] >= 'm' && s[i] <= 'o') {
            while (s[i] >= 'm' && s[i] <= 'o') {
                cur += oc[6];
                s[i]--;
            }
            if (cur.back() == prev.back()) {
                cout << '#';
            }
            cout << cur;
            prev = cur;
            continue;
        }
        if (s[i] >= 'p' && s[i] <= 's') {
            while (s[i] >= 'p' && s[i] <= 's') {
                cur += oc[7];
                s[i]--;
            }
            if (cur.back() == prev.back()) {
                cout << '#';
            }
            cout << cur;
            prev = cur;
            continue;
        }
        if (s[i] >= 't' && s[i] <= 'v') {
            while (s[i] >= 't' && s[i] <= 'v') {
                cur += oc[8];
                s[i]--;
            }
            if (cur.back() == prev.back()) {
                cout << '#';
            }
            cout << cur;
            prev = cur;
            continue;
        }
        if (s[i] >= 'w' && s[i] <= 'z') {
            while (s[i] >= 'w' && s[i] <= 'z') {
                cur += oc[9];
                s[i]--;
            }
            if (cur.back() == prev.back()) {
                cout << '#';
            }
            cout << cur;
            prev = cur;
            continue;
        }
    }
}
