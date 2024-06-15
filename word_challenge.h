#ifndef WORD_CHALLENGE_H
#define WORD_CHALLENGE_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <chrono>
#include <random>
#include <set>
#include "utils.h"
#include "TSP.h"

using namespace std;
using namespace chrono;

// Function to read space-separated characters and store them in a vector
vector<char> readLetters()
{
  string input;
  cout << "Enter a set of letters (space-separated): ";
  cin.ignore(); // To ignore any remaining newline characters in the input buffer
  getline(cin, input);

  istringstream iss(input);
  vector<char> letters;
  char letter;
  while (iss >> letter)
  {
    letters.push_back(letter);
  }

  return letters;
}

vector<string> findWords(TernarySearchTree &dictionary, vector<char> &letters)
{
  // Sort the vector to ensure that we can generate permutations in lexicographical order
  sort(letters.begin(), letters.end());

  // Use a set to store permutations and avoid duplicates
  set<string> permutations;

  do
  {
    permutations.insert(accumulate(letters.begin(), letters.end(), string("")));
  } while (next_permutation(letters.begin(), letters.end()));

  vector<string> foundWords;
  for (const auto &perm : permutations)
  {
    dictionary.findWords(perm, foundWords);
  }
  return foundWords;
}

#endif // WORD_CHALLENGE_H
