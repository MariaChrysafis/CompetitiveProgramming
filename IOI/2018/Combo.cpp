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
#include "combo.h"
 
using namespace std;
string oracle = "YBY";
bool isSubstring (string substr, string s) {
    for (int i = 0; i < s.length(); i++) {
        if (i + substr.length() - 1 < s.length() && s.substr(i, substr.length()) == substr) {
            return true;
        }
    }
    return false;
}
 
/*
int press (string p) {
    cout << "QUERY " << p << '\n';
    for (int i = 1; i <= oracle.size(); i++) {
        if (!isSubstring(oracle.substr(0, i), p)) {
            return i - 1;
        }
    }
    return oracle.size();
}
 */
 
string guess_sequence (int N) {
    string so_far = "";
    if (press("AX") != 0) {
        if (press("A")) {
            so_far = "A";
        } else {
            so_far = "X";
        }
    } else {
        if (press("B")) {
            so_far = "B";
        } else {
            so_far = "Y";
        }
    }
    if (N == 1) {
        return so_far;
    }
    for (int i = 1; i < N - 1; i ++) {
        vector<string> pos;
        for (string c: {"A", "B", "X", "Y"}) {
            if (so_far[0] != c[0]) {
                pos.push_back(c);
            }
        }
        string qry;
        for (string s: pos) {
            qry += so_far + pos[0] + s;
        }
        qry += so_far + pos[1];
        int res = press(qry);
        //cout << "GET " << res << '\n';
        if (res == so_far.size()) {
            so_far += pos[2];
        } else if (res == so_far.size() + 1) {
            so_far += pos[1];
        } else {
            so_far += pos[0];
        }
    }
    assert(so_far.size() == N - 1);
    if (press(so_far + 'A' + so_far + 'X') == N) {
        if (press(so_far + 'A') == N) {
            return so_far + 'A';
        } else {
            return so_far + 'X';
        }
    } else {
        if (press(so_far + 'B') == N) {
            return so_far + 'B';
        } else {
            return so_far + 'Y';
        }
    }
    assert(so_far == oracle);
}
 
/*
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    //cout << press("XXYYABYABXAY");
    cout << guess_sequence(oracle.size());
}
*/
