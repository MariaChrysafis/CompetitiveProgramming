package com.company;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

class Solution {
    private static class Node {
        String sub = "";                       // a substring of the input string
        List<Integer> ch = new ArrayList<>();  // list of child nodes
    }

    private static class SuffixTree {
        private final List<Node> nodes = new ArrayList<>();

        public SuffixTree(String str) {
            nodes.add(new Node());
            for (int i = 0; i < str.length(); ++i) {
                addSuffix(str.substring(i));
            }
        }

        private void addSuffix(String suf) {
            int n = 0;
            int i = 0;
            while (i < suf.length()) {
                char b = suf.charAt(i);
                List<Integer> children = nodes.get(n).ch;
                int x2 = 0;
                int n2;
                while (true) {
                    if (x2 == children.size()) {
                        // no matching child, remainder of suf becomes new node.
                        n2 = nodes.size();
                        Node temp = new Node();
                        temp.sub = suf.substring(i);
                        nodes.add(temp);
                        children.add(n2);
                        return;
                    }
                    n2 = children.get(x2);
                    if (nodes.get(n2).sub.charAt(0) == b) {
                        break;
                    }
                    x2++;
                }
                // find prefix of remaining suffix in common with child
                String sub2 = nodes.get(n2).sub;
                int j = 0;
                while (j < sub2.length()) {
                    if (suf.charAt(i + j) != sub2.charAt(j)) {
                        // split n2
                        int n3 = n2;
                        // new node for the part in common
                        n2 = nodes.size();
                        Node temp = new Node();
                        temp.sub = sub2.substring(0, j);
                        temp.ch.add(n3);
                        nodes.add(temp);
                        nodes.get(n3).sub = sub2.substring(j);  // old node loses the part in common
                        nodes.get(n).ch.set(x2, n2);
                        break;  // continue down the trie
                    }
                    j++;
                }
                i += j;  // advance past part in common
                n = n2;  // continue down the trie
            }
        }

        public void visualize() {
            if (nodes.isEmpty()) {
                System.out.println("<empty>");
                return;
            }
            visualize_f(0, "");
        }

        private void visualize_f(int n, String pre) {
            List<Integer> children = nodes.get(n).ch;
            if (children.isEmpty()) {
                System.out.println(". " + nodes.get(n).sub);
                return;
            }
            System.out.println("┐ " + nodes.get(n).sub);
            for (int i = 0; i < children.size() - 1; i++) {
                Integer c = children.get(i);
                System.out.print(pre + "├─");
                visualize_f(c, pre + "│ ");
            }
            System.out.print(pre + "└─");
            visualize_f(children.get(children.size() - 1), pre + "  ");
        }
    }

    static class TrieNode {
        TrieNode[] children;
        List<Integer> palindromeList;
        int index;

        TrieNode() {
            children = new TrieNode[26];
            palindromeList = null;
            index = -1;
        }
    }

    static class Trie {
        TrieNode root;

        public Trie() {
            root = new TrieNode();
        }

        public void insert(String str, int index) {
            TrieNode cur = root;
            int n = str.length();
            int i = 0;
            while (i < n) {
                if (isPalindrome(str, i, n - 1)) {
                    if (cur.palindromeList == null) {
                        cur.palindromeList = new ArrayList<>();
                    }
                    cur.palindromeList.add(index);
                }
                int ch = str.charAt(i) - 'a';
                if (cur.children[ch] == null) {
                    cur.children[ch] = new TrieNode();
                }
                cur = cur.children[ch];
                i++;
            }
            cur.index = index;
        }

        public void find(String str, int index, List<List<Integer>> result) {
            TrieNode cur = root;
            int n = str.length();
            int i = n - 1;
            for (; i >= 0; i--) {
                if (cur.index != -1) {
                    if (isPalindrome(str, 0, i)) {
                        result.add(Arrays.asList(cur.index, index));
                    }
                }
                int ch = str.charAt(i) - 'a';
                if (cur.children[ch] == null) {
                    return;
                }
                cur = cur.children[ch];
            }
            if (cur.palindromeList != null) {
                for (Integer ind : cur.palindromeList) {
                    result.add(Arrays.asList(ind, index));
                }
            }
            if (cur.index != -1 && cur.index != index) {
                result.add(Arrays.asList(cur.index, index));
            }
        }

        public boolean isPalindrome(String str, int begin, int end) {
            while (begin < end && str.charAt(begin) == str.charAt(end)) {
                begin++;
                end--;
            }
            return begin >= end;
        }
    }


    public List<List<Integer>> palindromePairs(String[] words) {
        Trie trie = new Trie();
        List<List<Integer>> result = new ArrayList<>();
        for (int i = 0; i < words.length; i++) {
            trie.insert(words[i], i);
        }
        for (int i = 0; i < words.length; i++) {
            trie.find(words[i], i, result);
        }
        return result;
    }


    public static void main(String[] args) {
        int u = 0;
        System.out.println(new Solution().maximizeXor(new int[]{0, 1, 2, 3, 4}, new int[][]{{3, 1}, {1, 3}, {5, 6}}));
    }
}
