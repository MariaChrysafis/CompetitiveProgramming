/**
 * code generated by JHelper
 * More info: https://github.com/AlexeyDmitriev/JHelper
 * @author Maria Chrysafis
 */



#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <iomanip>
#include <unordered_map>
#include <unordered_set>
#include <random>
#include <queue>
#include <string>
using namespace std;

class CDoubleProfiles {
public:
    const int MOD1 = (int)1e9 + 7;
    const int MOD2 = (int)1e9 + 9;
    const int MOD3 = 999999733;

    long long mult1 (long long x, long long y) {
        return (x * y) % MOD1;
    }

    long long mult2 (long long x, long long y) {
        return (x * y) % MOD2;
    }

    long long mult3 (long long x, long long y) {
        return (x * y) % MOD3;
    }

	void solve(std::istream& in, std::ostream& out) {
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);
	    int N, M;
	    in >> N >> M;
	    vector<long long> prod1, prod2, prod3;
	    vector<long long> vec1(N), vec2(N), vec3(N);
        std::random_device dev;
        std::uniform_int_distribution<std::mt19937::result_type> dist1000000000(2,(int)1e9); // distribution in range [1, 6]
	    for (int i = 0; i < N; i++) {
	        vec1[i] = rand();
	        vec2[i] = rand();
	        vec3[i] = rand();
            vec1[i] %= MOD1;
            vec2[i] %= MOD2;
            vec3[i] %= MOD3;
            //out << vec3[i] << ' ';
	    }
	    prod1.assign(N, 1), prod2.assign(N, 1), prod3.assign(N, 1);
	    vector<pair<int,int>> edges;
	    for (int i = 0; i < M; i++) {
	        int u, v;
	        in >> u >> v;
	        u--, v--;
            prod1[u] = mult1(prod1[u], vec1[v]);
            prod1[v] = mult1(prod1[v], vec1[u]);
            prod2[u] = mult2(prod2[u], vec2[v]);
            prod2[v] = mult2(prod2[v], vec2[u]);
            prod3[u] = mult3(prod3[u], vec3[v]);
            prod3[v] = mult3(prod3[v], vec3[u]);
	        edges.emplace_back(u, v);
	    }
	    map<pair<pair<long long, long long> ,long long>, long long> myMap;
	    for (int i = 0; i < N; i++) {
	        myMap[{{prod1[i], prod2[i]}, prod3[i]}]++;
	    }
	    long long ans = 0;
	    for (auto& p: myMap) {
	        ans += (p.second * (p.second - 1))/2;
	    }
	    for (auto& p: edges) {
	        //cout << mult3(prod3[p.first], vec3[p.first]) << " " << mult3(prod3[p.second], vec3[p.second]) << '\n';
	        if (mult1(prod1[p.first], vec1[p.first]) == mult1(prod1[p.second], vec1[p.second])
	        && mult2(prod2[p.first], vec2[p.first]) == mult2(prod2[p.second], vec2[p.second])
	        && mult3(prod3[p.first], vec3[p.first]) == mult3(prod3[p.second], vec3[p.second])) {
	            ans++;
	            //out << "YES\n";
	        }
	    }
	    out << ans;
	}
};


int main() {
	CDoubleProfiles solver;
	std::istream& in(std::cin);
	std::ostream& out(std::cout);
	solver.solve(in, out);
	return 0;
}
