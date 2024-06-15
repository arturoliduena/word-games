#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <set>
#include "utils.h"
#include "TSP.h"
#include "wordle.h"

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
  const int MAX_GUESSES = 100;
  vector<int> wordLengths = {3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20}; // Example word lengths to test
  vector<int> numGamesList = {5, 10, 20};                                                      // Example number of games to test

  // Open the CSV file to write results
  ofstream outFile("wordle_experiment_results.csv");
  outFile << "WordLength,NumGames,AvgRounds,AvgTime\n";
  for (int wordLength : wordLengths)
  {
    for (int numGames : numGamesList)
    {
      int rounds = 0;
      double totalTime = 0.0;

      for (int i = 0; i < numGames; ++i)
      {
        WordleKeeper keeper(wordLength);
        WordleGuesser guesser(wordLength);
        WordleGame wordleGame(MAX_GUESSES);
        auto start = high_resolution_clock::now();

        while (!wordleGame.isGameOver())
        {

          string guess = guesser.makeGuess(dictionary);
          string feedback = keeper.feedback(guess);

          if (wordleGame.isCorrectGuess(guess, feedback))
          {
            break;
          }
          guesser.updateFeedback(feedback, guess);
        }
        auto end = high_resolution_clock::now();
        duration<double> elapsed = end - start;
        totalTime += elapsed.count();

        // Update total number of rounds:
        rounds += wordleGame.getGuessCount();
      }

      // Calculate average words found and average CPU time
      double avgRounds = rounds / static_cast<double>(numGames);
      double avgTime = totalTime / numGames;
      // Write results to CSV file
      outFile << wordLength << "," << numGames << "," << avgRounds << "," << avgTime << "\n";
    }
  }
  outFile.close();
  return 0;
}
