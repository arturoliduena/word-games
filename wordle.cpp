#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <set>
#include "utils.h"
#include "TSP.h"
#include "wordle.h"

int main()
{
  TernarySearchTree dictionary;
  string result = loadDictionary("dictionary.txt", dictionary);
  if (result != "Success")
  {
    cout << "Failed to load dictionary. Exiting." << endl;
    return 1;
  }
  const int MAX_GUESSES = 20;

  string mode;
  cout << "Enter mode (interactive/automatic): ";
  cin >> mode;
  cout << "Enter word length: ";
  int wordLength;
  cin >> wordLength;

  if (mode == "interactive")
  {
    int play;
    cout << "play as keeper (1) or guesser (2): ";
    cin >> play;

    if (play == 1)
    {

      WordleKeeper keeper(wordLength);
      WordleGame wordleGame(MAX_GUESSES);
      while (!wordleGame.isGameOver())
      {

        cout << "Enter guess (word length " << wordLength << "): ";
        string guess;
        cin >> guess;
        if (guess.length() != wordLength)
        {
          cout << "Invalid guess. Word length should be " << wordLength << endl;
          continue;
        }
        string feedback = keeper.feedback(guess);

        if (wordleGame.isCorrectGuess(guess, feedback))
        {
          cout << "Correct guess!" << endl;
          break;
        }
        cout << "Feedback: " << feedback << endl;
      }
      keeper.print_secret();
    }
    else if (play == 2)
    {
      WordleGuesser guesser(wordLength);
      WordleGame wordleGame(MAX_GUESSES);

      while (!wordleGame.isGameOver())
      {
        // Select a random word of specified length from the dictionary
        string guess = guesser.makeGuess(dictionary);
        cout << "Guess: " << guess << endl;
        cout << "give the answers(the strings of 0s, 1s, and 2's - length " << wordLength << "): ";
        string feedback;
        cin >> feedback;
        if (feedback.length() != wordLength)
        {
          cout << "Invalid answers. Word length should be " << wordLength << endl;
          continue;
        }
        if (wordleGame.isCorrectGuess(guess, feedback))
        {
          cout << "Correct guess!" << endl;
          break;
        }
        guesser.updateFeedback(feedback, guess);
        cout << "Feedback: " << feedback << endl;
      }
    }
  }
  else if (mode == "automatic")
  {

    int numGames;
    cout << "Enter number of games: ";
    cin >> numGames;
    int rounds = 0;
    double totalTime = 0.0;

    for (int i = 0; i < numGames; ++i)
    {
      cout << "Game " << i + 1 << endl;
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
          cout << "Correct guess!" << endl;
          break;
        }
        guesser.updateFeedback(feedback, guess);
        cout << "Feedback: " << feedback << endl;
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

    cout << "Average number of rounds: " << avgRounds << endl;
    cout << "Average CPU time per game: " << avgTime << " seconds" << endl;
  }

  return 0;
}
