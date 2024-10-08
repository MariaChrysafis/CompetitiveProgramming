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
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <string>
#include <random>
using namespace std;
class ELuckyTree {
public:
    struct dsu{
        vector<int> parent;
        vector<long long> compSize;
        int n;
        void fill(){
            parent.resize(n), compSize.resize(n);
            for(int i = 0; i < n; i++){
                parent[i] = i, compSize[i] = 1;
            }
        }
        int find_head(int x){
            if(x == parent[x]){
                return x;
            }
            return find_head(parent[x]);
        }
        void join(int x, int y){
            x = find_head(x);
            y = find_head(y);
            if(x == y){
                return;
            }
            if(compSize[x] > compSize[y]){
                swap(x,y);
            }
            parent[x] = y;
            compSize[y] += compSize[x];
        }
    };
    bool lucky (string s) {
        for (int i = 0; i < s.length(); i++) {
            if (s[i] != '4' && s[i] != '7') {
                return false;
            }
        }
        return true;
    }
    void solve(std::istream& in, std::ostream& out) {
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);
        dsu d;
        //int n;
        in >> d.n;
        d.fill();
        for (int i = 0; i < d.n - 1; i++) {
            int u, v;
            in >> u >> v;
            u--, v--;
            string s;
            in >> s;
            if (!lucky(s)) {
                d.join(u, v);
            }
        }
        long long ans = 0;
        for (int i = 0; i < d.n; i++) {
            ans += (d.n - d.compSize[d.find_head(i)]) * (d.n - d.compSize[d.find_head(i)] - 1);
        }
        out << ans;
    }
};


int main() {
	ELuckyTree solver;
	std::istream& in(std::cin);
	std::ostream& out(std::cout);
	solver.solve(in, out);
	return 0;
}
