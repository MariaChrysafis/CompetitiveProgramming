    /**
     * code generated by JHelper
     * More info: https://github.com/AlexeyDmitriev/JHelper
     * @author
     */
     
    #include <iostream>
    #include <fstream>
     
    #include <iostream>
    #include <vector>
    using namespace std;
    class BStrangeList {
    public:
        long long largestPowerOfTwo(long long x){
          long long counter = 0;
          while(x % 2 == 0){
            x /= 2;
            counter++;
          }
          return counter;
        }
        void f(std::istream& in, std::ostream& out) {
          long long n;
          long long x;
          in >> n >> x;
          vector<pair<long long,long long>> v;
          int arr[n];
          for(int i = 0; i < n; i++){
            in >> arr[i];
            v.push_back({arr[i],1});
          }
          for(int i = 0; i < v.size(); i++){
            if(v[i].first % x == 0){
              v.push_back({v[i].first/x, x * v[i].second});
            }else{
              break;
            }
          }
          long long ans = 0;
          for(pair<long long,long long> i: v){
            ans += i.first * i.second;
          }
          out << ans << endl;
        }
    	void solve(std::istream& in, std::ostream& out) {
    	  int t;
    	  in >> t;
    	  while(t--){
    	    f(in, out);
    	  }
    	}
    };
     
     
    int main() {
    	BStrangeList solver;
    	std::istream& in(std::cin);
    	std::ostream& out(std::cout);
    	solver.solve(in, out);
    	return 0;
    }
