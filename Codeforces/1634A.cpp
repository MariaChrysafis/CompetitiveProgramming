#include <cmath>
#include <cassert>
#include <iostream>
#include <set>
#include <climits>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <type_traits>
#include <string>
#include <queue>
#include <map>

using namespace std;
typedef int64_t ll;

bool isPalindrome (string s) {
	string str = s;
	reverse(str.begin(), str.end());
	return (str == s);
}

int main() {
	ios_base::sync_with_stdio(0);
  	cin.tie(0);
  	int t;
  	cin >> t;
  	while (t--) {
  		int n, k; cin >> n >> k;
  		string s; cin >> s;
  		if (k == 0) {
  			cout << 1 << '\n';
  			continue;
  		}
  		if (isPalindrome(s)) {
  			cout << "1\n";
  			continue;
  		}
  		cout << "2\n";
  	}
}
