#include <bits/stdc++.h>
#pragma GCC target("lzcnt,popcnt")
 
using namespace std;

const int MOD = 1e9 + 7;
const int BUF_SZ = 1 << 15;

inline namespace Input {
char buf[BUF_SZ];
int pos;
int len;
char next_char() {
	if (pos == len) {
		pos = 0;
		len = (int)fread(buf, 1, BUF_SZ, stdin);
		if (!len) {
			return EOF;
		}
	}
	return buf[pos++];
}

int read_int() {
	int x;
	char ch;
	int sgn = 1;
	while (!isdigit(ch = next_char())) {
		if (ch == '-') {
			sgn *= -1;
		}
	}
	x = ch - '0';
	while (isdigit(ch = next_char())) {
		x = x * 10 + (ch - '0');
	}
	return x * sgn;
}
} // namespace Input
inline namespace Output {
char buf[BUF_SZ];
int pos;

void flush_out() {
	fwrite(buf, 1, pos, stdout);
	pos = 0;
}

void write_char(char c) {
	if (pos == BUF_SZ) {
		flush_out();
	}
	buf[pos++] = c;
}

void write_int(int x) {
	static char num_buf[100];
	if (x < 0) {
		write_char('-');
		x *= -1;
	}
	int len = 0;
	for (; x >= 10; x /= 10) {
		num_buf[len++] = (char)('0' + (x % 10));
	}
	write_char((char)('0' + x));
	while (len) {
		write_char(num_buf[--len]);
	}
	write_char('\n');
}

// auto-flush output when program exits
void init_output() { assert(atexit(flush_out) == 0); }
} // namespace Output


void bad () {
    cout << "NOT MAGIC\n";
    exit(0);
}

void tester (vector<vector<int> > & arr) {
    for (int i = 0; i < arr.size(); i++) {
        if (arr[i][i] != 0) {
            bad();
        }
        for (int j = 0; j < arr.size(); j++) {
            if (arr[i][j] != arr[j][i]) {
                bad();
            }
        }
    }
    for (int i = 0; i < arr.size(); i++) {
        for (int j = 0; j < arr[0].size(); j++) {
            vector<int> v;
            v.push_back(j - 1), v.push_back(i - 1);
            v.push_back(j + 1), v.push_back(i + 1);
            for (int k: v) {
                if (k < 0 || k == arr.size()) continue;
                if (arr[i][j] > max(arr[i][k], arr[j][k])) {
                    bad();
                }
            }
        }
    }
    map<int,vector<pair<int,int> > > myMap;
    for (int i = 0; i < arr.size(); i++) {
        for (int j = 0; j < arr[0].size(); j++) {
            myMap[arr[i][j]].push_back(make_pair(i, j));
        }
    }
    bitset<2500> bs[(int)arr.size()];
    for (auto& p: myMap) {
        for (auto& q: p.second) {
            if (q.first >= q.second) {
                if ((bs[q.first] & bs[q.second]).any()) {
                    bad();
                }
            }
        }
        for (auto& q: p.second) {
            bs[q.first].set(q.second);
        }
    }
}

int main() {
    init_output();
    int n = read_int();
    vector<vector<int> > arr(n);
    for (int i = 0; i < n; i++) {
        arr[i].resize(n);
        for (int j = 0; j < n; j++) {
            arr[i][j] = read_int();
        }
    }
    tester(arr);
    cout << "MAGIC\n";
}
