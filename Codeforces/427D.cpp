#include <bits/stdc++.h>
#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
//#pragma GCC optimization ("unroll-loops")
using namespace std;
class SuffixArray {
public:
    vector<int> ans;
    SuffixArray(string s) {
        s += '$';
        int64_t n = s.length();
        vector<int> eq(s.length());
        vector<pair<char, int> > vec;
        for (int i = 0; i < s.length(); i++) {
            vec.push_back(make_pair(s[i], i));
        }
        sort(vec.begin(), vec.end());
        int cntr = 0;
        eq[vec[0].second] = 0;
        for (int i = 1; i < vec.size(); i++) {
            eq[vec[i].second] = eq[vec[i - 1].second] + (vec[i].first != vec[i - 1].first);
        }
        for (int i = 0; (1 << i) < n; i++) {
            vector<pair<int64_t, int> > tot;
            for (int j = 0; j < vec.size(); j++) {
                tot.push_back(make_pair((n + 1) * eq[j] + eq[(j + (1 << i)) % n], j));
            }
            sort(tot.begin(), tot.end());
            eq[tot[0].second] = 0;
            for (int j = 1; j < vec.size(); j++) {
                eq[tot[j].second] = eq[tot[j - 1].second] + (tot[j].first != tot[j - 1].first);
            }
        }
        vector<pair<int,int> > v;
        for (int i = 0; i < n; i++) {
            v.push_back(make_pair(eq[i], i));
        }
        sort(v.begin(), v.end());
        for (int i = 1; i < v.size(); i++) {
            ans.push_back(v[i].second);
        }
        //cout << '\n';
    }
};
pair<int,int> new_interval (pair<int,int> interval, SuffixArray& sa, string&s, char c, int len) {
    //len = j - i
    int l = interval.first, r = interval.second;
    while (l != r) {
        int m = (l + r)/2;
        if (s[sa.ans[m] + len] >= c) {
            r = m;
        } else {
            l = m + 1;
        }
    }
    interval.first = l;
    l = interval.first, r = interval.second;
    while (l != r) {
        int m = (l + r + 1)/2;
        if (s[sa.ans[m] + len] <= c) {
            l = m;
        } else {
            r = m - 1;
        }
    }
    interval.second = l;
    if (s[sa.ans[l] + len] != c) {
        return make_pair(-1, -1);
    }
    return interval;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string s, t;
    cin >> s >> t;
	SuffixArray sa(s), sb(t);
    s += '$';
    int myMin = INT_MAX;
    for (int i = 0; i < t.length(); i++) {
        pair<int,int> interval1, interval2;
        interval1.first = 0, interval1.second = sa.ans.size() - 1;
        interval2.first = 0, interval2.second = sb.ans.size() - 1;
        for (int j = i; j < t.length(); j++) {
            interval1 = new_interval(interval1, sa, s, t[j], j - i);
            interval2 = new_interval(interval2, sb, t, t[j], j - i); //
            if (interval1.first == -1) {
                break;
            }
            if (interval1.first == interval1.second && interval2.first == interval2.second) {
                myMin = min(myMin, j - i + 1);
            }
        }
    }
    if (myMin == INT_MAX) {
        myMin = -1;
    }
    cout << myMin;
}
