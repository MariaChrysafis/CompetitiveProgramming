        /**
         * code generated by JHelper
         * More info: https://github.com/AlexeyDmitriev/JHelper
         * @author
         */
         
        #include <iostream>
        #include <fstream>
         
        #include <iostream>
        #include <algorithm>
        using namespace std;
        class CStrangeBirthdayParty {
        public:
            void f(std::istream& in, std::ostream& out) {
              int n, m;
              in >> n >> m;
              int k[n];
              int c[m];
              for(int i = 0; i < n; i++){
                in >> k[i];
                k[i]--;
              }
              for(int i = 0; i < m; i++){
                in >> c[i];
              }
              sort(k, k + n);
              sort(c, c + m);
              int arr[n];
              for(int i = 0; i < n; i++){
                arr[i] = c[k[i]];
              }
              sort(arr, arr + n);
              reverse(arr, arr + n);
              long long sum = 0;
              for(int i = 0; i < n; i++){
                if(i < m){
                  arr[i] = min(arr[i], c[i]);
                }
                sum += arr[i];
              }
              out << sum << endl;
            }
        	void solve(std::istream& in, std::ostream& out) {
              ios_base::sync_with_stdio(false);
              cin.tie(NULL);
        	  int t;
        	  in >> t;
        	  while(t--){
        	    f(in, out);
        	  }
        	}
        };
         
         
        int main() {
        	CStrangeBirthdayParty solver;
        	std::istream& in(std::cin);
        	std::ostream& out(std::cout);
        	solver.solve(in, out);
        	return 0;
        }
