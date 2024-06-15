#include <iostream>
#include <unordered_set>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <chrono>
#include <set>
#include "utils.h"
#include "TSP.h"

using namespace std;
using namespace chrono;

class WordleGame
{
private:
  int MAX_GUESSES;
  int guessCount;

public:
  WordleGame(int maxGuesses) : MAX_GUESSES(maxGuesses), guessCount(0) {}
  bool isCorrectGuess(const string &guess, const string &feedback)
  {
    guessCount++;
    return feedback == string(guess.length(), '2');
  }
  bool isGameOver() const
  {
    return guessCount >= MAX_GUESSES;
  }

  int getGuessCount() const
  {
    return guessCount;
  }
};

class WordleKeeper
{
private:
  string secret;
  set<char> secret_set;

public:
  WordleKeeper(const size_t length)
  {
    string word = getRandomWordOfLength("dictionary.txt", length);
    cout << "Secret word: " << word << endl;
    secret = word;
    secret_set = set<char>(secret.begin(), secret.end());
  }

  string feedback(const string &guess)
  {
    string result(secret.length(), '0');
    vector<bool> secretUsed(secret.length(), false);
    for (size_t i = 0; i < guess.length(); ++i)
    {
      if (guess[i] == secret[i])
      {
        result[i] = '2';
        secretUsed[i] = true;
      }
      else if (secret_set.find(guess[i]) != secret_set.end())
      {
        result[i] = '1';
      }
    }
    return result;
  }
};

class WordleGuesser
{
private:
  const size_t length;

public:
  WordleGuesser(const size_t length) : length(length) {}

  string makeGuess()
  {
    // Select a random word of specified length from the dictionary
    return getRandomWordOfLength("dictionary.txt", length);
  }
};

int main()
{
  TernarySearchTree dictionary;
  string result = loadDictionary("dictionary.txt", dictionary);
  if (result != "Success")
  {
    cout << "Failed to load dictionary. Exiting." << endl;
    return 1;
  }
  const int MAX_GUESSES = 6;

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
    }
    else if (play == 2)
    {
      WordleGuesser guesser(wordLength);
      WordleGame wordleGame(MAX_GUESSES);

      while (!wordleGame.isGameOver())
      {
        // Select a random word of specified length from the dictionary
        string guess = guesser.makeGuess();
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

        string guess = guesser.makeGuess();
        string feedback = keeper.feedback(guess);

        if (wordleGame.isCorrectGuess(guess, feedback))
        {
          cout << "Correct guess!" << endl;
          break;
        }
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
