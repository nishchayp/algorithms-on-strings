#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <utility>

using std::cin;
using std::cout;
using std::endl;
using std::map;
using std::string;
using std::vector;
using std::pair;
using std::make_pair;

struct Node {
  pair<int, int> range;
  vector<Node> next;
};

void insert_suffix_to_trie(const string& text, Node* trie, int l_idx) {
  Node* curr_node = trie;
  for (int k = l_idx; k < text.size(); k++) {
    bool match = false;
    for (int i = 0; i < curr_node->next.size(); i++) {
      if (text[k] == text[curr_node->next[i].range.first]) {
        curr_node = &(curr_node->next[i]);
        match = true;
        break;
      }
    }
    if (!match) {
      Node new_node;
      new_node.range.first = k;
      new_node.range.second = k;
      curr_node->next.push_back(new_node);
      curr_node = &(curr_node->next.back());
    }
  }
}

void build_trie(const string& text, Node* trie) {
  for (int i = text.size() - 1; i >= 0; i--) {
    insert_suffix_to_trie(text, trie, i);
  }
}

void compress_trie(const string& text, Node* trie) {
  for (int i = 0; i < trie->next.size(); i++) {
    compress_trie(text, &(trie->next[i]));
  }
  if (trie->next.size() == 1) {
    Node desc = trie->next[0];
    trie->range.second = desc.range.second;
    trie->next.clear();
    for (int i = 0; i < desc.next.size(); i++)
      trie->next.push_back(desc.next[i]);
  }
}

void traverse_trie(const string& text, Node* trie, vector<string> &result) {
  for (int i = 0; i < trie->next.size(); i++) {
    traverse_trie(text, &(trie->next[i]), result);
  }
  int l = trie->range.first;
  int r = trie->range.second;
  if (l != -1) {
    result.push_back(text.substr(l, r - l + 1));
  }
}


// Build a suffix tree of the string text and return a vector
// with all of the labels of its edges (the corresponding 
// substrings of the text) in any order.
vector<string> ComputeSuffixTreeEdges(const string& text) {
  vector<string> result;
  // Implement this function yourself
  Node trie;
  trie.range = make_pair(-1, -1);
  build_trie(text, &trie);
  compress_trie(text, &trie);
  traverse_trie(text, &trie, result);
  return result;
}

int main() {
  string text;
  cin >> text;
  vector<string> edges = ComputeSuffixTreeEdges(text);
  for (int i = 0; i < edges.size(); ++i) {
    cout << edges[i] << endl;
  }
  return 0;
}
