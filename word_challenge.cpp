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
#include "word_challenge.h"
#include "TSP.h"

using namespace std;
using namespace chrono;

int main()
{
  TernarySearchTree dictionary;
  string result = loadDictionary("dictionary.txt", dictionary);
  if (result != "Success")
  {
    cout << "Failed to load dictionary. Exiting." << endl;
    return 1;
  }

  string mode;
  cout << "Enter mode (interactive/automatic): ";
  cin >> mode;

  if (mode == "interactive")
  {
    vector<char> letters = readLetters();
    vector<string> foundWords = findWords(dictionary, letters);
    for (const auto &word : foundWords)
    {
      cout << word << endl;
    }
  }
  else if (mode == "automatic")
  {
    int numGames, wordLength;
    cout << "Enter number of games: ";
    cin >> numGames;
    cout << "Enter word length: ";
    cin >> wordLength;

    // Variables to store total words found and total time
    int totalWordsFound = 0;
    double totalTime = 0.0;

    // Seed for random number generator
    random_device rd;
    mt19937 gen(rd());

    for (int i = 0; i < numGames; ++i)
    {
      // Select a random word of specified length from the dictionary
      string word = getRandomWordOfLength("dictionary.txt", wordLength);

      // Rearrange its letters randomly
      // Scramble the letters of the selected word
      vector<char> scrambledLetters(word.begin(), word.end());
      shuffle(scrambledLetters.begin(), scrambledLetters.end(), gen);

      // Measure time taken
      auto start = high_resolution_clock::now();

      // Find all possible words
      vector<string> foundWords = findWords(dictionary, scrambledLetters);

      auto end = high_resolution_clock::now();
      duration<double> elapsed = end - start;
      totalTime += elapsed.count();

      // Update total words found
      totalWordsFound += foundWords.size();
    }

    // Calculate average words found and average CPU time
    double avgWordsFound = totalWordsFound / static_cast<double>(numGames);
    double avgTime = totalTime / numGames;

    cout << "Average words found: " << avgWordsFound << endl;
    cout << "Average CPU time (seconds): " << avgTime << endl;
  }
  else
  {
    cout << "Invalid mode. Please enter 'interactive' or 'automatic'." << endl;
  }

  return 0;
}
