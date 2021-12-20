#include <algorithm>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <random>
#include <set>
#include <stack>
#include <vector>

using namespace std;
struct segmentTreePoint {
    vector<int> v;
    vector<int> vec;
    vector<int> addLater;

    void upd(int dum, int tl, int tr, int &l, int &r, int val) {
        if (tr < l || tl > r) {
            return;
        }
        if (tl >= l && tr <= r) {
            addLater[dum] += val;
            return;
        }
        int mid = (tl + tr) >> 1;
        dum = dum << 1;
        upd(dum, tl, mid, l, r, val);
        upd(dum + 1, mid + 1, tr, l, r, val);
    }

    void upd(int l, int r, int val) { upd(1, 0, v.size() - 1, l, r, val); }

    int get(int x) {
        int cur = x + v.size();
        int ans = 0;
        while (true) {
            ans += addLater[cur];
            if (cur == 0) {
                break;
            }
            cur /= 2;
        }
        return ans;
    }

    void resz(int n) {
        v.assign((1 << (int)ceil(log2(n))), 0);
        vec.assign(v.size() * 2, 0);
        addLater.assign(v.size() * 2, 0);
    }
};
struct Changer {
    set<int> occurences;
    string s;
    segmentTreePoint pref;
    int right(int x) {
        auto it = occurences.upper_bound(x);
        if (it == occurences.end()) {
            return -1;
        }
        return (*it);
    }
    int left(int x) {
        auto it = occurences.lower_bound(x);
        if (it == occurences.begin()) {
            return -1;
        }
        it--;
        return (*it);
    }
    void generate(int n) {
        pref.resz(n + 1);
        s.assign(n, '#');
    }
    void generate_string(string str) {
        generate(str.length());
        s = str;
        occurences.clear();
        for (int i = 0; i < s.length(); i++) {
            if (s[i] != '#') {
                occurences.insert(i);
            }
        }
        for (int i = 0; i < s.length(); i++) {
            pref.upd(i + 1, i + 1, pref.get(i));
            if (left(i) == -1) continue;
            if (s[left(i)] == 'H' && s[i] == 'L') {
                pref.upd(i + 1, i + 1, 1);
            }
        }
    }
    void remove(int x) {
        if (s[x] == '#') {
            return;
        }
        occurences.erase(x);
        if (s[x] == 'L') {
            s[x] = '#';
            if (left(x) == -1 || s[left(x)] == 'L') {
                //left(x) == -1 --> ....*L*...H...H.
                //s[left(x)] == 'L' --> ..H..L...*L*.....
                return;
            }
            if (right(x) == -1) {
                //cout << "YES\n";
                if (s[left(x)] == 'H') {
                    //....H..*L*......
                    pref.upd(x + 1, s.length(), -1);
                } else {
                    //....L...*L*...
                    return;
                }
                return;
            }
            if (s[right(x)] == 'H') {
                //....H...*L*...H..
                pref.upd(x + 1, s.length(), -1);
            } else {
                //...H....*L*...L
                pref.upd(x + 1, s.length(), -1);
                pref.upd(right(x) + 1, s.length(), 1);
            }
        } else {
            s[x] = '#';
            if (right(x) == -1 || s[right(x)] == 'H') {
                //right(x) == -1 --> ..H..*H*.....
                //s[right(x)] = -1 --> ....L..*H*...H......
                return;
            }
            if (left(x) == -1) {
                if (s[right(x)] == 'L') {
                    //..........*H*...L..
                    pref.upd(right(x) + 1, s.length(), -1);
                } else {
                    //..........*H*...H..
                    return;
                }
                return;
            }
            if (s[left(x)] == 'L') {
                //.....L....*H*...L....
                pref.upd(right(x) + 1, s.length(), -1);
            } else {
                //.....H....*H*...L....
                return;
            }
        }
    }
    void add (int x, char c) {
        if (s[x] == c) {
            return;
        }
        remove(x);
        s[x] = c;
        occurences.insert(x);
        if (c == 'L') {
            if (left(x) == -1) {
                //....*L*..L.
                return;
            }
            if (right(x) == -1) {
                if (left(left(x)) == -1) {
                    if (s[left(x)] == 'H') {
                        //...H....*L*...
                        pref.upd(x + 1, s.length(), 1);
                    } else {
                        //...L....*L*...
                        return;
                    }
                } else if (s[left(left(x))] == 'L') {
                    if (s[left(x)] == 'H') {
                        //.L..H..*L*.....
                        pref.upd(x + 1, s.length(), 1);
                    } else {
                        //..L...L...*L*
                        return;
                    }
                } else if (s[left(left(x))] == 'H') {
                    if (s[left(x)] == 'H') {
                        //...H...H....*L*
                        pref.upd(x + 1, s.length(), 1);
                    } else {
                        //...H...L....*L*
                        return;
                    }
                }
                return;
            } else {
                if (s[left(x)] == 'L') {
                    //....L....*L*
                    return;
                } else if (s[left(x)] == 'H'){
                    if (s[right(x)] == 'H') {
                        //.H..*L*..H.
                        pref.upd(x + 1, s.length(), 1);
                    } else if (s[right(x)] == 'L'){
                        //.H...*L*..L...
                        pref.upd(right(x) + 1, s.length(), -1);
                        pref.upd(x + 1, s.length(), 1);
                    }
                }
            }
        } else if (c == 'H'){
            if (right(x) == -1) {
                //..L..*H*.....
                return;
            }
            //there is stuff to the left
            if (left(x) == -1) {
                if (right(right(x)) == -1) {
                    if (s[right(x)] == 'H') {
                        //.....*H*....H
                        return;
                    } else {
                        //.....*H*....L
                        pref.upd(x + 1, s.length(), 1);
                    }
                } else if (s[right(right(x))] == 'L') {
                    if (s[right(x)] == 'H') {
                        //......*H*.H..L.
                        return;
                    } else {
                        //......*H*.L..L.
                        pref.upd(x + 1, s.length(), 1);
                        return;
                    }
                } else if (s[right(right(x))] == 'H') {
                    if (s[right(x)] == 'H') {
                        //...*H*....H....H
                        return;
                    } else {
                        //.........*H*....L....H
                        pref.upd(right(x + 1), s.length(), 1);
                        return;
                    }
                }
            } else if (left(x) != -1){
                if (s[left(x)] == 'H') {
                    if (s[right(x)] == 'H') {
                        //..H..*H*..H..
                        return;
                    } else if (s[right(x)] == 'L'){
                        //...H....*H*...L..
                        return;
                    }
                } else if (s[left(x)] == 'L'){
                    if (s[right(x)] == 'H') {
                        //.L..*H*..H.
                        return;
                    } else if (s[right(x)] == 'L'){
                        //.L...*H*..L...
                        pref.upd(right(x) + 1, s.length(), 1);
                    }
                }
            }
        }
        assert(c == 'H' || c == 'L');
    }
    void print() {
        cout << s << '\n';
        for (int i = 0; i <= s.length(); i++) {
            cout << pref.get(i) << ' ';
        }
        cout << '\n';
        generate_string(s);
        for (int i = 0; i <= s.length(); i++) {
            cout << pref.get(i) << ' ';
        }
        cout << '\n';
    }
};
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    int p[n];
    map<int,int> oc;
    for (int i = 0; i < n; i++) {
        cin >> p[i];
        oc[p[i]] = i;
    }
    oc[0] = -1;
    set<int> s;
    map<int,vector<pair<char,int>>> myMap;
    for (int i = 0; i < n; i++) {
        auto it = s.upper_bound(p[i]);
        pair<int,int> p1;
        if (it != s.begin()) {
            it--;
            p1 = {0, *it - 1};
        } else {
            p1 = {-1, -1};
        }
        pair<int,int> p2 = {max(p1.second, p1.first) + 1, p[i] - 1};
        pair<int,int> p3;
        p3.first = max(max(p2.second, p2.first), max(p1.first, p1.second)) + 1;
        it = s.upper_bound(p[i]);
        if (it == s.end()) {
            p3.second = n;
        } else {
            p3.second = *it - 1;
        }
        pair<int,int> p4;
        p4.first = max(max(max(p3.second, p3.first), max(p2.first, p2.second)), max(p1.first, p1.second)) + 1;
        p4.second = n;
        s.insert(p[i]);
        //cout << p1.first << " " << p2.first << " " << p3.first << " " << p4.first << '\n';
        if (p1.second != -1) {
            myMap[p1.first].push_back({'#', i});
        }
        if (p2.second != -1) {
            myMap[p2.first].push_back({'H', i});
        }
        if (p3.second != -1) {
            myMap[p3.first].push_back({'L', i});
        }
        if (p4.second >= p4.first) {
            //cout << p4.first << '\n';
            myMap[p4.first].push_back({'#', i});
        }
    }

    Changer changer;
    changer.generate(n);
    string str;
    str.assign(n, '#');
    int cntr = 0;
    for (auto& q: myMap) {
        cntr++;
        for (auto& pr: q.second) {
            //cout << pr.first << " " << pr.second << ' ';
            str[pr.second] = pr.first;
            if (pr.first == '#') changer.remove(pr.second);
            else changer.add(pr.second, pr.first);
        }
        int x = changer.pref.get(max(oc[cntr - 1], oc[cntr]) + 1);
        cout << x << '\n';

    }

    return 0;
}
