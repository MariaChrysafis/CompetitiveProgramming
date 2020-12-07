#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <queue>
#include <deque>
#include <bitset>
#include <iterator>
#include <list>
#include <stack>
#include <map>
#include <set>
#include <functional>
#include <numeric>
#include <utility>
#include <limits>
#include <cstdio>
#include <cmath>
const int INF = 100000;
using namespace std;
pair<int, int> step[] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0},
              {-1, -1}, {-1, 1}, {1, -1}, {1, 1}};
vector<vector<char> > board;
vector<vector<char> > identity;
void print(vector<vector<char> > v) {
  cout << "   0 1 2 3 4 5 6 7" << endl;
  cout << " +-----------------+" << endl;
  for (int i = 0; i < 8; i++) {
    cout << i << "| ";
    for (int j = 0; j < 8; j++) { cout << v[i][j] << " "; }
    cout << "|";
    cout << endl;
  }
  cout << " +-----------------+";
  cout << endl;
}
bool valid(int i, int j) { return (i >= 0 && j >= 0 && i < 8 && j < 8); }

if (c == 'w') return 'b';
return 'w';
}
int get_rate(vector<vector<char> > arr, char c) {
  int rating = 0;
  for (int i = 0; i < arr.size(); i++) {
    for (int j = 0; j < arr.size(); j++) {
      if (arr[i][j] == c) rating--;
    }
  }
  return rating;
}
vector<vector<char> > move(int i, int j, char c, vector<vector<char> > arr) {
  arr[i][j] = c;
  vector<vector<char> > orig = arr;
  bool okay = false;
  for (auto& p : step) {
    if (valid(i + p.first, j + p.second) &&
        arr[i + p.first][j + p.second] != '.') {
      okay = true;
    }
  }
  if (!okay) {
    return {{}};
  }
  for (int i1 = i + 1; i1 < 8; i1++) {
    if (arr[i1][j] == '.') break;
    if (arr[i1][j] == c) {
      for (int i2 = i; i2 <= i1; i2++) {
        arr[i2][j] = c;
      }
      break;
    }
  }
  for (int i1 = i - 1; i1 >= 0; i1--) {
    if (arr[i1][j] == '.') break;
    if (arr[i1][j] == c) {
      for (int i2 = i1; i2 <= i; i2++) {
        arr[i2][j] = c;
      }
      break;
    }
  }
  for (int j1 = j + 1; j1 < 8; j1++) {
    if (arr[i][j1] == '.') break;
    if (arr[i][j1] == c) {
      for (int j2 = j; j2 <= j1; j2++) {
        arr[i][j2] = c;
      }
      break;
    }
  }
  for (int j1 = j - 1; j1 >= 0; j1--) {
    if (arr[i][j1] == '.') break;
    if (arr[i][j1] == c) {
      for (int j2 = j1; j2 <= j; j2++) {
        arr[i][j2] = c;
      }
      break;
    }
  }
  for (int a = 1; a < 8; a++) {
    if (valid(-a + i, a + j) && arr[-a + i][a + j] == '.') break;
    if (valid(-a + i, a + j) && arr[-a + i][a + j] == c) {
      for (int a1 = 1; a1 < a; a1++) {
        arr[-a1 + i][a1 + j] = c;
      }
      break;
    }
  }
  for (int a = 1; a < 8; a++) {
    if (valid(i + a, j - a) && arr[i + a][j - a] == '.') break;
    if (valid(i + a, j - a) && arr[i + a][j - a] == c) {
      for (int a1 = 0; a1 <= a; a1++) {
        arr[i + a1][j - a1] = c;
      }
      break;
    }
  }
  for (int a = 1; a < 8; a++) {
    if (valid(i + a, j + a) && arr[i + a][j + a] == '.') break;
    if (valid(i + a, j + a) && arr[i + a][j + a] == c) {
      for (int a1 = 0; a1 < a; a1++) {
        arr[i + a1][j + a1] = c;
      }
    }
  }
  for (int a = 1; a < 8; a++) {
    if (valid(i - a, j - a) && arr[i - a][j - a] == '.') break;
    if (valid(i - a, j - a) && arr[i - a][j - a] == c) {
      for (int a1 = 0; a1 < a; a1++) arr[i - a1][j - a1] = c;
    }
  }
  if (orig == arr) {

    return {{}};
  }
  return arr;
}
vector<vector<char> > grandchild(char c, vector<vector<char> > orig_board) {
  vector<vector<char> > new_board = orig_board;
  vector<vector<char> > worst_board;
  int myMin = INF;
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      if (orig_board[i][j] != '.') continue;
      new_board = move(i, j, c, orig_board);
      if (new_board.size() != 8) {
        new_board = orig_board;
        continue;
      }
      if (get_rate(new_board, c) < myMin) {
        myMin = get_rate(new_board, c);
        worst_board = new_board;
      }
      new_board = orig_board;
    }
  }
  return worst_board;
}
pair<int, int> child(char c) {
  vector<vector<char> > new_board = board;
  int myMax = -INF;
  pair<int, int> optimal = {-1, -1};
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {

      if (board[i][j] != '.') continue;
      new_board = move(i, j, c, board);
      if (new_board.size() != 8) {
        new_board = board;
        continue;
      }

      vector<vector<char> > pos = grandchild(op(c), new_board);
      if (get_rate(pos, c) > myMax) {
        myMax = get_rate(pos, c);
        optimal = make_pair(i, j);
      }
    }
  }
  return optimal;
}
int main() {
  ios_base::sync_with_stdio(0); cin.tie(0); board.resize(8);
  for (int i = 0; i < 8; i++) {
    board[i].resize(8);
    for (int j = 0; j < 8; j++) { board[i][j] = '.'; }
  }
  board[4][4] = 'b';
  board[3][4] = 'w';
  board[3][3] = 'b';
  board[4][3] = 'w';
  char c;
  cin >> c;

  if (c == 'w') {

    int x = 64;
    while (x--) {
      pair<int, int> p = child('b');
      cout << p.first << " " << p.second << endl;
      board = move(p.first, p.second, 'b', board);
      print(board);
      cout << endl;
      int a, b;
      cin >> a >> b;
      board = move(a, b, 'w', board);
      print(board);
      cout << endl;
    }
  } else {
    int x = 64;
    print(board);
    while (x--) {
      int a, b;
      cin >> a >> b;
      board = move(a, b, 'b', board);
      print(board);
      cout << endl;
      pair<int, int> p = child('w');
      cout << p.first << " " << p.second << endl;
      board = move(p.first, p.second, 'w', board);
      cout << endl;
    }
  }

  return 0;
}
