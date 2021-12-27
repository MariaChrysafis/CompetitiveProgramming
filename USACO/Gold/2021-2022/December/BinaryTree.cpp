#include <vector>
#include <algorithm>
#include <map>
using std::string;
using std::vector;

class Node {
 private:
  Node *left;
  Node *right;
  const int value;
  bool isRightLeaf;
  int count;
 public:

  Node(int input, bool isRightLeaf0, int count0)
      : value(input), left(nullptr), right(nullptr), isRightLeaf(isRightLeaf0), count(count0) {
  }

  std::vector<int> evaluateResults() {
    vector<std::pair<int, int>> innerMap;
    traverse(innerMap);
    sort(innerMap.begin(), innerMap.end());

    std::vector<int> output;
    for (auto item : innerMap) {
      output.push_back(item.second);
    }
    delete this;
    return output;
  }

  Node *insert(int myValue, char fromRightLeaf) {
    if (myValue < value) {
      if (left != nullptr) {
        return left->insert(myValue, true);
      } else {
        return left = new Node(myValue, true, this->count);
      }
    } else {
      if (right != nullptr) {
        return right->insert(myValue, false);
      } else {
        return right = new Node(myValue, false, this->count + (fromRightLeaf ? 1 : 0));
      }
    }
  }

 private:
  void traverse(vector<std::pair<int, int>> &innerMap) {
    if (left != nullptr) {
      left->traverse(innerMap);
      delete left;
    }
    if (right != nullptr) {
      right->traverse(innerMap);
      delete right;
    }
    innerMap.push_back(std::pair<int, int>(value, count + (isRightLeaf ? 1 : 0)));
  }
};

std::vector<int> treeSolution(std::vector<int> input, bool debug) {
  Node *root = new Node(input[0], false, 0);
  for (int index = 1; index < input.size(); index++) {
    root->insert(input[index], false);
  }
  return root->evaluateResults();
}