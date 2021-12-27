#include <iostream>
#include <vector>
#include <algorithm>

static int COUNT = 4;
using std::string;
using std::vector;

class Node {
 private:
  Node *left;
  Node *right;
  const int value;
 public:
  Node(int input) : value(input), left(nullptr), right(nullptr) {
  }

  void cleanup() {
    if (left != nullptr) {
      left->cleanup();
    }
    if (right != nullptr) {
      right->cleanup();
    }
    delete this;
  }

  Node *insert(Node *node) {
    if (node->getValue() == value) {
      return this;
    } else if (node->getValue() < value) {
      if (left != nullptr) {
        return left->insert(node);
      } else {
        return left = new Node(node->getValue());
      }
    } else {
      if (right != nullptr) {
        return right->insert(node);
      } else {
        return right = new Node(node->getValue());
      }
    }
  }

  Node *getLeft() const {
    return left;
  }

  int getValue() const {
    return value;
  }

  Node *getRight() const {
    return right;
  }

  static void printTreeInTwoDimensions(Node *root, int horizontalSpace) {
    // Base case
    if (root == nullptr) {
      return;
    }

    horizontalSpace += COUNT;

    printTreeInTwoDimensions(root->getRight(), horizontalSpace);

    for (int i = COUNT; i < horizontalSpace; i++) {
      std::cout << " ";
    }
    std::cout << root->getValue() << "\n";

    printTreeInTwoDimensions(root->getLeft(), horizontalSpace);
  }
};

std::vector<int> treeSolution(std::vector<int> input, bool debug) {
  std::vector<int> output;
  Node *root = new Node(input[0]);
  Node *top = root;
  for (int index = 1; index < input.size(); index++) {
    root->insert(new Node(input[index]));
  }
  if (debug) {
    Node::printTreeInTwoDimensions(top, 0);
  }
  output.push_back(0);
  for (int v = 1; v <= input.size(); v++) {
    root = top;
    char last = ' ';
    int count = 0;
    if (debug) {
      std::cout << v << " ";
    }
    do {
      char ndir;
      bool eq = root->getValue() == v;
      if (root->getValue() > v) {
        root = root->getLeft();
        ndir = 'H';
      } else if (root->getValue() <= v) {
        root = root->getRight();
        ndir = 'L';
      }
      if (ndir == 'L' && last == 'H') {
        count++;
      }
      if (debug) {
        std::cout << ndir << " ";
      }
      last = ndir;
      if (eq) {
        break;
      }
    } while (true);
    if (debug) {
      std::cout << count << "\n";
    }
    output.push_back(count);
  }
  top->cleanup();
  return output;
}