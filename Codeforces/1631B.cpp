/*
Notes: 
1) At the end, all of the vertices will be equal to the last vertex on the end.

*/
#include <cmath>
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

#define ll long long

int suffixSame (vector<int> v) {
	int cur = v.back();
	int cntr = 0;
	while (!v.empty() && v.back() == cur) {
		cntr++;
		v.pop_back();
	}
	return cntr;
}

void solve () {
    int N;
    cin >> N;
    vector<int> arr;
    for (int i = 0; i < N; i++) {
    	int x; 
    	cin >> x; 
    	arr.push_back(x);
    }
    int cur = arr.back();
    int sz = suffixSame(arr);
    int lstUpdate = arr.size();
    int cntr = 0;
    for (int i = arr.size() - 1; i >= 0; i--) {
    	if (arr[i] == cur) {
    		continue;
    	}
    	//cout << i << '\n';
    	//cout << lstUpdate << '\n';
    	//cout << sz << '\n';
    	if (lstUpdate - i + 1 < sz) {
    		continue;
    	}
    	sz = arr.size() - i;
    	lstUpdate = i;
    	cntr++;
    }
    cout << cntr << '\n';
}

int main () {
    int T;
    cin >> T;
    while (T--) {
        solve();
    }
}
