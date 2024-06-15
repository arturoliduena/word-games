#ifndef UTILITIES_H
#define UTILITIES_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <random>
#include "TSP.h"

using namespace std;

struct WordEntry
{
  string word;
  int frequency;
};

bool compareByFrequency(const WordEntry &a, const WordEntry &b)
{
  return a.frequency > b.frequency;
}

string loadDictionary(string filename, TernarySearchTree &tst)
{
  ifstream file(filename);
  if (!file)
  {
    cerr << "Error: Could not open dictionary file." << endl;
    return "Error";
  }

  vector<WordEntry> words;
  string line;
  while (getline(file, line))
  {
    istringstream ss(line);
    string word;
    int frequency;
    if (getline(ss, word, ':') && (ss >> frequency))
    {
      words.push_back({word, frequency});
    }
  }

  // Sort words by frequency in descending order
  sort(words.begin(), words.end(), compareByFrequency);

  // Insert words into the TST
  for (const auto &entry : words)
  {
    tst.insert(entry.word);
  }

  file.close();
  return "Success";
}

vector<string> readWordsFromFile(const string &filename)
{
  ifstream file(filename);
  vector<string> words;
  string line;

  if (!file.is_open())
  {
    cerr << "Unable to open file" << endl;
    return words;
  }

  while (getline(file, line))
  {
    // Find the position of the colon
    size_t colonPos = line.find(':');
    if (colonPos != string::npos)
    {
      // Extract the word (substring before the colon)
      string word = line.substr(0, colonPos);
      words.push_back(word);
    }
  }

  file.close();
  return words;
}

string getRandomWordOfLength(const string &filename, size_t length)
{
  ifstream file(filename);
  vector<string> words;
  string line;

  if (!file.is_open())
  {
    cerr << "Unable to open file" << endl;
    return "";
  }

  while (getline(file, line))
  {
    // Find the position of the colon
    size_t colonPos = line.find(':');
    if (colonPos != string::npos)
    {
      // Extract the word (substring before the colon)
      string word = line.substr(0, colonPos);
      if (word.length() == length)
      {
        words.push_back(word);
      }
    }
  }

  file.close();

  if (words.empty())
  {
    return ""; // No word of the specified length found
  }

  // Generate a random index
  random_device rd;  // non-deterministic generator
  mt19937 gen(rd()); // to seed mersenne twister.
  uniform_int_distribution<> dis(0, words.size() - 1);

  size_t randomIndex = dis(gen);

  return words[randomIndex];
}

#endif // UTILITIES_H