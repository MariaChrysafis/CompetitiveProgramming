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
#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")

using namespace std;

int P;
using namespace std;
/*
 * Disjoint Sparse Table taken from https://codeforces.com/blog/entry/79108
 */
template <typename T, int64_t identity>
class DisjointSparseTable {
public:
    explicit DisjointSparseTable(vector<T> arr) {
        this->arr = arr;
        // Find the highest cnt such that pow2 = 2^cnt >= x
        int pow2 = 1, cnt = 0;
        for (; pow2 < arr.size(); pow2 *= 2, ++cnt);

        arr.resize(pow2, identity);
        sum.resize(cnt, vector<T>(pow2));

        for(int level = 0; level < sum.size(); ++level) {
            for(int block = 0; block < 1 << level; ++block) {
                const auto start = block << (sum.size() - level);
                const auto end = (block + 1) << (sum.size() - level);
                const auto middle = (end + start) / 2;
                auto val = arr[middle];
                sum[level][middle] = val % P;
                for(int x = middle + 1; x < end; ++x) {
                    val = (val * arr[x]) % P;
                    sum[level][x] = val;
                }

                val = arr[middle - 1];
                sum[level][middle - 1] = val;
                for(int x = middle-2; x >= start; --x) {
                    val = (val * arr[x]) % P;
                    sum[level][x] = val;
                }
            }
        }
    }
    /*! Returns Monoid sum over range [l, r)*/
    T query(int l, int r) const {
        if (l == r) {
            return arr[l] % P;
        }
        const auto pos_diff = 63 - __builtin_clzll(l ^ r);
        const auto level = sum.size() - 1 - pos_diff;
        return (sum[level][l] * sum[level][r]) % P;
    }
private:
    vector<vector<T>> sum;
    vector<T> arr;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    cin >> T;
    while (T--) {
        int N, Q;
        cin >> N >> P >> Q;
        vector<int64_t> vec(N);
        for (int i = 0; i < N; i++) {
            cin >> vec[i];
            vec[i] %= P;
        }
        DisjointSparseTable<int64_t, 1> sp{vec};
        vector<int> b(Q/64 + 2);
        for (int i = 0; i < b.size(); i++) {
            cin >> b[i];
        }
        pair<int64_t,int64_t> pr;
        int x = -1;
        for (int i = 0; i < Q; i++) {
            x++; x %= P;
            if (i % 64 == 0) {
                pr.first = b[i/64] + x;
                pr.second = b[i/64 + 1] + x;
            } else {
                pr.first += x;
                pr.second += x;
            }
            pr.first %= N, pr.second %= N;
            if (pr.first > pr.second) {
                swap(pr.first, pr.second);
            }
            x = sp.query(pr.first, pr.second);
        }
        cout << (x + 1) % P << '\n';
    }

}
