/**
 * code generated by JHelper
 * More info: https://github.com/AlexeyDmitriev/JHelper
 * @author
 */
 
#include <iostream>
#include <algorithm>
#include <fstream>
 
#include <iostream>
#include <algorithm>
#include <fstream>
 
 
 
 
 
 
 
 
 
 
#include <vector>
#include <cmath>
#include <set>
#pragma GCC target("avx2")
#pragma GCC optimization("O3")
#pragma GCC optimization("unroll-loops")
#pragma optimization_level 3
#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math,O3")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
using namespace std;
class DTheNumberOfPairs {
public:
  struct NT {
    int MAX;
    vector<int> isPrime;
    vector<int> primes;
    vector<int> pf;
    vector<int> ind;
    void init() {
      isPrime.resize(MAX);
      for (int i = 0; i < MAX; i++) {
        isPrime[i] = -1;
      }
    }
    void Solve() {
      isPrime[0] = 0;
      isPrime[1] = 0;
      for (int i = 2; i < MAX; i++) {
        if (isPrime[i] == -1) {
          for (int j = 2 * i; j < MAX; j += i) {
            if (isPrime[j] == -1) {
              isPrime[j] = i; // the smallest prime factor of i
            }
          }
        }
      }
    }
    void generate() {
      for (int i = 0; i < MAX; i++) {
        if (isPrime[i] == -1) {
          primes.push_back(i);
        }
      }
      ind.resize(MAX);
      for (int i = 0; i < primes.size(); i++) {
        ind[primes[i]] = i;
      }
    }
    int factorize(int x) {
      if (isPrime[x] == 0) {
        return 0;
      }
      if (isPrime[x] == -1) {
        pf.push_back(x);
        return x;
      }
      pf.push_back(isPrime[x]);
      return factorize(x / isPrime[x]);
    }
    int GCD(int a, int b){
      if(min(a, b) == 0) return max(a, b);
      return GCD(max(a, b) % min(a, b), min(a, b));
    }
    int primefact(int x) {
      pf.clear();
      factorize(x);
      if(pf.size() == 0){
        return 0;
      }
      int cntr = 1;
      for(int i = 0; i < pf.size() - 1; i++){
        if(pf[i] != pf[i + 1]){
          cntr++;
        }
      }
      return cntr;
    }
  };
  int pwr[30];
  NT nt;
  int num(int prod){
    int x = nt.primefact(prod);
    return pwr[x];
  }
  void f(std::istream &in, std::ostream &out) {
    int c, d, x;
    in >> c >> d >> x;
    vector<int> factors;
    for(int G = 1; G < sqrt(x); G++){
      if(x % G == 0){
        factors.push_back(G);
      }
    }
    int sz = factors.size();
    for(int i = 0; i < sz; i++){
      factors.push_back(x/factors[i]);
    }
    if(floor(sqrt(x)) * floor(sqrt(x)) == x){
      factors.push_back(sqrt(x));
    }
    int counter = 0;
    for(int G: factors){
      int ab = x/G + d;
      if(ab % c == 0){
        counter += num(ab/c);
      }
    }
    out << counter << '\n';
  }
  void solve(std::istream &in, std::ostream &out) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    nt.MAX = 20000010;
    nt.init();
    nt.Solve();
    nt.generate();
    pwr[0] = 1;
    for(int i = 1; i < 30; i++){
      pwr[i] = pwr[i - 1] * 2;
    }
    int t;
    in >> t;
    while(t--){
      f(in, out);
    }
  }
};
 
int main() {
	DTheNumberOfPairs solver;
	std::istream& in(std::cin);
	std::ostream& out(std::cout);
	solver.solve(in, out);
	return 0;
}
