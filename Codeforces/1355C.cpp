#include <iostream>
using namespace std;
int main() {
  long long A, B, C, D;
  cin >> A >> B >> C >> D;
  long long cntr = 0;
  for (int z = C; z <= D; z++) {
    if (z + 1 - B <= A) {
      cntr += (C - B + 1) * (B - A + 1);
    } else if (z + 1 - B <= B) {
      cntr += (C - B + 1) * (2 * B - z);
    }
    long long left = max(A, z + 1 - C);
    long long right = min(B, z - B);
    if (left <= right) {
      cntr += (C - z) * (right - left + 1) +
              (left + right) * (right - left + 1) / 2;
    }
  }
  cout << cntr << endl;
}
