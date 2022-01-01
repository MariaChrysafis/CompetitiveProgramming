#include <iostream>
#include <vector>
#include <chrono>
#include <cstdint>
#include <algorithm>
#include <set>
#include <cmath>
#include <queue>
#include <deque>
#include <cassert>
#include <map>

using namespace std;

typedef int64_t ll;
vector<string> vec;
string generate (vector<int> v) {
    string s = "";
    for (int i: v) {
        s += vec[i];
    }
    return s;
}

vector<int> find_min (vector<int> v1, vector<int> v2) {
    bool b1 = false;
    for (int i: v1) {
        if (i == -1) {
            b1 = true;
        }
    }
    bool b2 = false;
    for (int i: v2) {
        if (i == -1) {
            b2 = true;
        }
    }
    if (b1 && b2) return {-1};
    if (b1) return v2;
    if (b2) return v1;
    string s1 = generate(v1);
    string s2 = generate(v2);
    if (s1 < s2) {
        return v1;
    } else {
        return v2;
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N, K;
    cin >> N >> K;
    vec.resize(N);
    int len = 0;
    for (int i = 0; i < N; i++) {
        cin >> vec[i];
        len += vec[i].size();
    }
    vector<int> dp[K + 1][len + 1];
    for (int i = 0; i <= K; i++) {
        for (int j = 0; j <= len; j++)  {
            dp[i][j] = {-1};
        }
    }
    dp[0][0] = {};
    for (int i = 1; i <= K; i++) {
        for (int j = 1; j <= len; j++) {
            //find best dp[i][j]
            for (int ind = 0; ind < vec.size(); ind++) {
                if (vec[ind].size() <= j) {
                    bool fine = true;
                    for (int val: dp[i - 1][j - vec[ind].size()]) {
                        if (val == ind) {
                            fine = false;
                            break;
                        }
                    }
                    if (!fine) {
                        continue;
                    }
                    dp[i - 1][j - vec[ind].size()].push_back(ind);
                    dp[i][j] = find_min(dp[i][j], dp[i - 1][j - vec[ind].size()]);
                    dp[i - 1][j - vec[ind].size()].pop_back();
                }
            }
        }
    }
    vector<int> myMin = {-1};
    for (int i = 0; i <= len; i++) {
        myMin = find_min(dp[K][i], myMin);
    }
    cout << generate(myMin);
}
