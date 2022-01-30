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
int main() {
	int t;
	cin >> t;
	while (t--) {
		int n;
		cin >> n;
    	string s;
    	cin >> s;
    	if (s.length() >= 3) {
    		cout << "NO\n";
    		continue;
    	}
    	if (s == "11" || s == "00") {
    		cout << "NO\n";
    		continue;
    	}
    	cout << "YES\n";
	}

}
