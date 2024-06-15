#ifndef WORDLE_H
#define WORDLE_H

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
    secret = getRandomWordOfLength("dictionary.txt", length);
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

  void print_secret() const
  {
    cout << "Secret word: " << secret << endl;
  }
};

class WordleGuesser
{
private:
  const size_t length;
  set<string> guesses;
  set<char> mandatory_char;
  string feedback;
  string memo;

public:
  WordleGuesser(const size_t length) : length(length), feedback(length, '0'), memo(length, '0') {}

  string makeGuess(TernarySearchTree &dictionary)
  {
    // Select a random word of specified length from the dictionary
    vector<string> foundWords;

    dictionary.findPartialWords(memo, foundWords);
    // Remove words that have already been guessed
    for (auto it = guesses.begin(); it != guesses.end(); ++it)
    {
      foundWords.erase(remove(foundWords.begin(), foundWords.end(), *it), foundWords.end());
    }

    // Remove words that do not contain characters in the mandatory set
    foundWords.erase(remove_if(foundWords.begin(), foundWords.end(),
                               [this](const string &word)
                               {
                                 for (char c : mandatory_char)
                                 {
                                   if (word.find(c) == string::npos)
                                   {
                                     return true;
                                   }
                                 }
                                 return false;
                               }),
                     foundWords.end());

    if (foundWords.size() > 0)
    {

      // Generate a random index
      random_device rd;  // non-deterministic generator
      mt19937 gen(rd()); // to seed mersenne twister.
      uniform_int_distribution<> dis(0, foundWords.size() - 1);

      size_t randomIndex = dis(gen);

      return foundWords[randomIndex];
    }
    else
    {
      return "";
    }
  }
  void updateFeedback(const string &newFeedback, const string &guess)
  {
    guesses.insert(guess);
    for (size_t i = 0; i < length; ++i)
    {
      if (newFeedback[i] == '2')
      {
        feedback[i] = '2';
        memo[i] = guess[i];
        mandatory_char.insert(guess[i]);
      }
      else if (newFeedback[i] == '1')
      {
        mandatory_char.insert(guess[i]);
      }
    }
  }
};

#endif // WORDLE_H