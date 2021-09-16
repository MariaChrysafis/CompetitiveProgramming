#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <map>
#include <set>
#include <iomanip>
#include <algorithm>
#include <queue>

#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
using namespace std;

template<typename T>
T readVal() {
    T n;
    cin >> n;
    return n;
}

template<typename T>
vector<T> readVector(T n) {
    vector<T> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }
    return v;
}

template<typename T>
void printVector(vector<T> vec) {
    cout << "! ";
    for (T x: vec) {
        cout << x << " ";
    }
    cout << endl;
}

string increment(string s1){
    int ind = s1.length() - 1;
    while(s1[ind] == '1'){
        s1[ind] = '0';
        ind--;
    }
    s1[ind] = '1';
    return s1;
}

string XOR(string s1, string s2) {
    string str;
    for(int i = 0; i < s1.length(); i++){
        if(s1[i] == s2[i]){
            str += '0';
        } else {
            str += '1';
        }
    }
    return str;
}

string rangeXor(string s1, string s2){
    if(s1 == s2) {
        return s1;
    }
    string cur = s1;
    string curXor = s1;
    while(cur != s2){
        cur = increment(cur);
        curXor = XOR(cur, curXor);
    }
    return curXor;
}

void solve() {
    int n;
    cin >> n;
    string s1, s2;
    cin >> s1 >> s2;
    if(s1[0] != s2[0]) {
        for(int i = 0; i < n; i++) cout << 1;
        return;
    }
    vector<int> differingPositions;
    bool valid = true;
    for(int i = 0; i < n; i++){
        if(s1[i] != s2[i]) {
            differingPositions.push_back(i);
            if(i > 5) {
                valid = false;
            }
        }
    }
    if(valid) {
        vector<string> pos = {s1};
        string cur = s1;
        while (cur != s2) {
            cur = increment(cur);
            pos.push_back(cur);
        }
        string myMax = s2;
        for (int i = 0; i < pos.size(); i++) {
            for (int j = i + 1; j < pos.size(); j++) {
                myMax = max(myMax, rangeXor(pos[i], pos[j]));
            }
        }
        cout << myMax << endl;
        return;
    }
    if(increment(s1) == s2 || s2.back() == '1'){
        cout << s2 << endl;
        return;
    }
    cout << increment(s2) << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
}
