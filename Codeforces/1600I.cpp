/**
 * code generated by JHelper
 * More info: https://github.com/AlexeyDmitriev/JHelper
 * @author Maria Chrysafis (Olympia)
 */



#include <iostream>
#include <fstream>
#include <vector>
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
class IBubbleStrike {
public:
    double combo3 (int N) {
        if (N < 0) return 0;
        return N * (N - 1) * (N - 2)/6;
    }
    double combo2 (int N) {
        if (N < 0) return 0;
        return N * (N - 1)/2;
    }
    double prob (int N, int K) {
        double ans = 0;
        ans += combo3(K)/combo3(N);
        ans += (combo2(K) * (N - K))/combo3(N);
        ans += K * combo2(N - K)/combo3(N) * 0.5;
        return ans;
    }
	void solve(std::istream& in, std::ostream& out) {
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);
        int N; double P;
        in >> N >> P;
        int l = 0;
        int r = N;
        while (l < r) {
            //out << l << " " << r << '\n';
            int m = (l + r)/2;
            if (prob(N, m) >= P) {
                r = m;
            } else {
                l = m + 1;
            }
        }
        out << l;
	}
};


int main() {
	IBubbleStrike solver;
	std::istream& in(std::cin);
	std::ostream& out(std::cout);
	solver.solve(in, out);
	return 0;
}
