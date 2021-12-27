#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <bitset>
#include <algorithm>
using namespace std::chrono;

std::vector<int> treeSolution(std::vector<int> inputVector, bool debug);
std::vector<int> goldenRun(std::vector<int> input, bool debug);

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  int n = 10000;
//    std::cin >> n;
  std::vector<int> inputPermutation;
  for (int i = 0; i < n; ++i) {
    inputPermutation.push_back(i + 1);
  }
  std::random_device rd;
  std::mt19937 g(rd());
  std::shuffle(inputPermutation.begin(), inputPermutation.end(), g);

  // print out content:
  if (false) {
    std::cout << "myvector contains:\n    ";
    for (std::vector<int>::iterator it = inputPermutation.begin(); it != inputPermutation.end(); ++it) {
      std::cout << *it << (*it >= 10 ? " " : "  ");
    }
  }

  std::cout << '\n';

  auto start = std::chrono::high_resolution_clock::now();
  std::vector<int> golden = goldenRun(inputPermutation, false);
  std::uint64_t duration1 =
      std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start).count();
  std::cout << duration1 << ", Brute force done " + std::to_string(golden.size()) << "\n";

  auto start2 = std::chrono::high_resolution_clock::now();
  std::vector<int> current = treeSolution(inputPermutation, false);
  std::uint64_t duration2 =
      std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start2).count();
  std::cout << duration2 << ", Binary Tree done " + std::to_string(current.size()) << "\n";
  std::cout << 1.0 * duration1 / duration2 << " times faster\n";

  bool failed = false;

  for (int i = 0; i < golden.size(); i++) {
    if (golden.at(i) != current.at(i)) {
      std::cout << i << " [" << golden.at(i) << " " << current.at(i) << "]"
                << (golden.at(i) != current.at(i) ? "*" : "") << '\n';
      failed = true;
    }
  }
  std::cout << (failed ? "Failed\n" : "Passed\n");
  return 0;
}

std::vector<int> goldenRun(std::vector<int> input, bool debug) {
  int n = input.size();
  std::vector<int> output;
  for (int i = 0; i <= n; i++) {
    std::vector<std::string> dbg(n);
    std::string s;
    int l = 0;
    int r = n;
    bool done = false;
    for (int j = 0; j < n; j++) {
      if (input[j] > i && r >= input[j] && !done) {
        s += 'H';
        dbg[j] = "H  ";
        r = input[j] - 1;
      } else if (input[j] <= i && l < input[j] && !done) {
        s += 'L';
        dbg[j] = "L  ";
        l = input[j];
      } else {
        if (input[j] > i) {
          dbg[j] = "   ";
        } else {
          dbg[j] = "l  ";
        }
      }
      if (r == l) {
        done = true;
      }
    }
    int cntr = 0;
    for (int j = 0; j < s.length(); j++) {
      if (s[j] == 'H' && s[j + 1] == 'L') {
        cntr++;
      }
    }
    if (debug) {
      std::string line;
      for (int j = 0; j < n; j++) {
        line.append(dbg[j]);
      }

      std::cout << ((i >= 10 ? " " : "  ")) << i << " " << line << " " << cntr << "\n";
    }
    output.push_back(cntr);
  }
  return output;
}