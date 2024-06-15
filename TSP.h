#ifndef TSP_H
#define TSP_H

#include <iostream>
#include <unordered_set>
#include <vector>
#include <string>

using namespace std;

typedef struct Node *TST;

struct Node
{
  char c;
  Node *left, *mid, *right;
  bool isEndOfString;
  int count;
  Node(char ch) : c(ch), left(nullptr), mid(nullptr), right(nullptr), isEndOfString(false), count(0) {}
};

class TernarySearchTree
{
private:
  Node *root;

  Node *insert(Node *t, const string &s, int i)
  {
    if (t == nullptr)
      t = new Node(s[i]);

    if (s[i] < t->c)
      t->left = insert(t->left, s, i);
    else if (s[i] > t->c)
      t->right = insert(t->right, s, i);
    else
    {
      t->count++;
      if (i + 1 < s.size())
        t->mid = insert(t->mid, s, i + 1);
      else
        t->isEndOfString = true;
    }

    return t;
  }

  Node *erase(Node *t, const string &s, int i)
  {
    if (t == nullptr)
      return nullptr;

    if (s[i] < t->c)
      t->left = erase(t->left, s, i);
    else if (s[i] > t->c)
      t->right = erase(t->right, s, i);
    else
    {
      t->count--;
      if (i + 1 < s.size())
        t->mid = erase(t->mid, s, i + 1);
      else
        t->isEndOfString = false;
    }

    return t;
  }

  bool search(Node *t, const string &s, int i)
  {
    if (t == nullptr)
      return false;

    if (s[i] < t->c)
      return search(t->left, s, i);
    else if (s[i] > t->c)
      return search(t->right, s, i);
    else
    {
      if (i + 1 < s.size())
        return t->isEndOfString;
      return search(t->mid, s, i + 1);
    }
  }

  void findWords(Node *t, const string &s, int i, const string &prefix, vector<string> &foundWords)
  {
    if (t == nullptr)
      return;

    if (s[i] < t->c)
      findWords(t->left, s, i, prefix, foundWords);
    else if (s[i] > t->c)
      findWords(t->right, s, i, prefix, foundWords);
    else
    {
      if (t->isEndOfString)
        foundWords.push_back(prefix + t->c);

      findWords(t->mid, s, i + 1, prefix + t->c, foundWords);
    }
  }

  int countSuffix(Node *t, const string &suffix, int i)
  {
    cout << suffix << " , " << i << endl;
    if (t == nullptr)
      return 0;

    if (suffix[i] < t->c)
      return countSuffix(t->left, suffix, i);
    else if (suffix[i] > t->c)
      return countSuffix(t->right, suffix, i);
    else
    {
      if (i + 1 < suffix.size())
        return countSuffix(t->mid, suffix, i + 1);
      else
      {

        return t->count;
      }
    }
    return 0;
  }

  void clear(Node *&t)
  {
    if (t == nullptr)
      return;
    clear(t->left);
    clear(t->mid);
    clear(t->right);
    delete t;
    t = nullptr;
  }

public:
  TernarySearchTree() : root(nullptr) {}

  ~TernarySearchTree()
  {
    clear(root);
  }

  void insert(const string &s)
  {
    root = insert(root, s, 0);
  }

  void erase(const string &s)
  {
    root = erase(root, s, 0);
  }

  int countSuffix(const string &suffix)
  {
    return !suffix.empty() ? countSuffix(root, suffix, suffix.size() - 1) : 0;
  }

  bool search(const string &s)
  {
    return search(root, s, 0);
  }

  void findWords(const string &s, vector<string> &foundWords)
  {
    findWords(root, s, 0, "", foundWords);
  }

  void reset()
  {
    clear(root);
  }
};

#endif // TSP_H