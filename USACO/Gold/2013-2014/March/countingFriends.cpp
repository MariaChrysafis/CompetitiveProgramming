#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>
#include <map>
#include <set>
#include <iomanip>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <string>
#include <random>
using namespace std;
class Problem3CountingFriends {
public:
    vector<int> removeZeroes (vector<int> v) {
        vector<int> ans;
        for (int i = 0; i < v.size(); i++) {
            if (v[i] > 0) {
                ans.push_back(v[i]);
            }
        }
        return ans;
    }
    bool valid (vector<int> ms) {
        ms = removeZeroes(ms);
        while (!ms.empty()) {
            sort(ms.begin(), ms.end());
            int x = ms.back();
            if (x < 0) {
                return false;
            }
            ms.pop_back();
            if (ms.size() < x) {
                return false;
            }
            for (int i = 0; i < x; i++) {
                ms[ms.size() - i - 1]--;
            }
            ms = removeZeroes(ms);
        }
        return true;
    }
    void solve(std::istream& in, std::ostream& out) {
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);
        int n;
        in >> n;
        vector<int> v(n + 1);
        int sum = 0;
        vector<int> multi;
        for (int i = 0; i < v.size(); i++) {
            in >> v[i];
            if (v[i] != 0) {
                multi.push_back(-v[i]);
            }
            sum += v[i];
        }
        sum %= 2;
        vector<int> pos;
        for (int i = 0; i < v.size(); i++) {
            if (sum % 2 != v[i] % 2) {
                continue;
            }
            vector<int> vec;
            for (int j = 0; j < v.size(); j++) {
                if (i != j) {
                    vec.push_back(v[j]);
                }
            }
            if (valid(vec)) {
                pos.push_back(i);
            }
        }
        out << pos.size() << '\n';
        for (int i = 0; i < pos.size(); i++) {
            out << pos[i] + 1;
            if (i != pos.size() - 1) {
                out << '\n';
            }
        }
        out << '\n';
    }
};
