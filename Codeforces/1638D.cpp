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
#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("Ofast")
#pragma GCC optimization ("unroll-loops")

using namespace std;

vector<vector<int>> arr;

void insert (set<int>& s, int x) {
	if (x != 0) {
		s.insert(x);
	}
}

bool square (int i, int j) {
	if (i + 1 >= arr.size() || j + 1 >= arr[0].size() || i < 0 || j < 0) {
		return false;
	}
	set<int> s;
	insert(s, arr[i][j]);
	insert(s, arr[i + 1][j]);
	insert(s, arr[i][j + 1]);
	insert(s, arr[i + 1][j + 1]);
	return (s.size() == 1);
}

int col (int i, int j) {
	if (i + 1 >= arr.size() || j + 1 >= arr[0].size() || i < 0 || j < 0) {
		return false;
	}
	set<int> s;
	insert(s, arr[i][j]);
	insert(s, arr[i + 1][j]);
	insert(s, arr[i][j + 1]);
	insert(s, arr[i + 1][j + 1]);
	return *s.begin();
}

void fill (int i, int j) {
	arr[i][j] = arr[i + 1][j] = arr[i][j + 1] = arr[i + 1][j + 1] = 0;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int N, M;
    cin >> N >> M;
    arr.resize(N);
    vector<vector<bool>> hasVisited(N);
    for (int i = 0; i < N; i++) {
    	arr[i].resize(M), hasVisited[i].resize(M);
    	for (int j = 0; j < M; j++) {
    		cin >> arr[i][j];
    	}
    }
    queue<pair<int,int>> q;
    for (int i = 0; i < N; i++) {
    	for (int j = 0; j < M; j++) {
    		if (square(i, j)) {
    			q.push({i, j});
    		}
    	}
    }
    vector<pair<pair<int,int>,int>> vec;
    while (!q.empty()) {
    	pair<int,int> p = q.front();
    	if (!square(p.first, p.second)) {
    		q.pop();
    		continue;
    	}
    	vec.push_back({{p.first, p.second}, col(p.first, p.second)});
    	fill(p.first, p.second);
    	q.pop();
    	for (int i = p.first - 2; i <= p.first + 2; i++) {
    		for (int j = p.second - 2; j <= p.second + 2; j++) {
    			if (square(i, j)) {
    				q.push(make_pair(i, j));
    			}
    		}
    	}
    }
    for (int i = 0; i < arr.size(); i++) {
    	for (int j = 0; j < arr[i].size(); j++) {
    		if (arr[i][j] != 0) {
    			cout << "-1\n";
    			return 0;
    		}
    	}
    }
    reverse(vec.begin(), vec.end());
    cout << vec.size() << '\n';
    for (auto& p: vec) {
    	cout << p.first.first + 1 << " " << p.first.second + 1 << " " << p.second << '\n';
    }
}
