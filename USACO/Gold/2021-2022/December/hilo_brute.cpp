#include <iostream>
#include <vector>
#include <set>
#include <chrono>
#include <random>
#include <queue>
#include <bitset>
#include <map>
#include <list>
#include <stack>
#include <algorithm>

template<class RandomIt, class RandomFunc>
void random_shuffle(RandomIt first, RandomIt last, RandomFunc &&r) {
    typename std::iterator_traits<RandomIt>::difference_type i, n;
    n = last - first;
    for (i = n - 1; i > 0; --i) {
        using std::swap;
        swap(first[i], first[r(i + 1)]);
    }
}

std::vector<int> goldenRun(std::vector<int> input);

std::vector<int> betterSolution(std::vector<int> inputVector);

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    int n;
    std::cin >> n;
    std::vector<int> inputPermutation;
    for (int i = 0; i < n; ++i) {
        inputPermutation.push_back(i + 1);
    }
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(inputPermutation.begin(), inputPermutation.end(), g);

    // print out content:
    std::cout << "myvector contains:\n    ";
    for (std::vector<int>::iterator it = inputPermutation.begin(); it != inputPermutation.end(); ++it) {
        std::cout << *it << (*it >= 10 ? " " : "  ");
    }

    std::cout << '\n';
    std::vector<int> golden = goldenRun(inputPermutation);
    std::cout << "Brute force done " + std::to_string(golden.size()) << "\n";
    std::vector<int> current = betterSolution(inputPermutation);
    std::cout << "Faster done " + std::to_string(current.size()) << "\n";

    for (int i = 0; i < golden.size(); i++) {
        if (golden.at(i) != current.at(i)) {
            std::cout << i << " [" << golden.at(i) << " " << current.at(i) << "]"
                      << (golden.at(i) != current.at(i) ? "*" : "") << '\n';
        }
    }
    std::cout << "done\n";
    return 0;
}

std::vector<int> goldenRun(std::vector<int> input) {
    int n = input.size();
    std::vector<int> output;
    for (int i = 0; i <= n; i++) {
        std::string s;
        std::string dbg;
        int l = 0;
        int r = n;
        bool done = false;
        for (int j = 0; j < n; j++) {
            if (input[j] > i && r >= input[j] && !done) {
                s += 'H';
                dbg += "H  ";
                r = input[j] - 1;
            } else if (input[j] <= i && l < input[j] && !done) {
                s += 'L';
                dbg += "L  ";
                l = input[j];
            } else {
                if (input[j] > i) {
                    dbg += "   ";
                } else {
                    dbg += "   ";
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
        std::cout << ((i >= 10 ? " " : "  ")) << i << " " << dbg << " " << cntr << "\n";
        output.push_back(cntr);
    }
    return output;
}
