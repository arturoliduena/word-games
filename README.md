# Word Challenge

In **Word Challenge**, the user provides a (multi)set of up to 17 letters, and the program produces all words that can be written using a subset of the given letters.

For example, if the user gives the letters `fE,T,F,H,R,R,E,O,Eg`, the program will output, by increasing length and then in alphabetical order, all the words that can be built using (some of) these letters. Examples include: `FOR`, `HER`, `ORE`, `THE`, ..., `HERE`, ..., `THEREFORE`. The dictionary contains only words of length ≥ 3, hence if given ` ≥ 3` the list of results starts with words of length 3 and ends with words of length ` (or smaller, if there were no words of length ` using all given letters).

Besides being able to play interactively with the user, the program also has an "automatic mode" in which it does the following repeatedly:
1. Picks a random word from the dictionary of given length ``
2. Rearranges its letters randomly
3. Supplies these letters to the function that generates the list of words which can be built from the given letters

In automatic mode, the user specifies the number of times the game will be played, and the length ``, and the program outputs the average number of words found and the average CPU time that the program takes to "solve" a word of length ``.

# Wordle

In **Wordle** ([Wordle on Wikipedia](https://en.wikipedia.org/wiki/Wordle)), the user can choose to play as either the keeper or the guesser. The length ` of the secret word is defined at the beginning of the game.

When playing as the guesser, the program chooses a secret word of length ` and for each round the player writes a valid word of length ` and the computer outputs a string of ` digits with the following meanings:
- `0`: The corresponding letter does not occur in the secret word.
- `1`: The corresponding letter occurs in the secret word but not at that position.
- `2`: The corresponding letter occurs at that position.

For example, if the secret word were `WORDS` and the current guess were `WHERE`, the program should output `20010` (the `W` was correctly guessed and the `R` is in the secret word, but it is not in the fourth position). The game ends when the secret word is correctly guessed or a MAX GUESSES bound is reached.

When the player takes the role of the keeper, the computer makes the guesses and the user provides the answers (the strings of `0`s, `1`s, and `2`s).

The program also offers an automatic mode in which the computer plays both as keeper and guesser (without cheating—the guesser function does not have access to the secret word, only its length and the history so far of guesses and answers). For the automatic mode, the human user specifies a length ` and a (large) number of games to be played. For each game, the keeper chooses a random word of length ` and a game is played between the keeper and the guesser. At the end, the program outputs the average number of rounds needed by the guesser to guess each secret word and the average CPU time to do it.

