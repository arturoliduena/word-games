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

  vector<int> wordLengths = {3, 4, 5, 6, 7, 8, 9, 10}; //, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20}; // Example word lengths to test
  vector<int> numGamesList = {5, 10, 20};
  // Open the CSV file to write results
  ofstream outFile("word_challenge_experiment_results.csv");
  outFile << "WordLength,NumGames,avgWordsFound,AvgTime\n";
  for (int wordLength : wordLengths)
  {
    for (int numGames : numGamesList)
    {
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
      // Write results to CSV file
      outFile << wordLength << "," << numGames << "," << avgWordsFound << "," << avgTime << "\n";
      cout << "Word length: " << wordLength << ", Num games: " << numGames << ", Avg words found: " << avgWordsFound << ", Avg time: " << avgTime << endl;
    }
  }
  outFile.close();
  return 0;
}
