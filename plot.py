import pandas as pd
import matplotlib.pyplot as plt


def plot_and_save_avg_results(df, ylabel, title, filename):
    # Group by WordLength and calculate mean for ylabel
    avg_results = df.groupby('WordLength')[ylabel].mean().reset_index()

    plt.figure(figsize=(10, 6))
    plt.plot(avg_results['WordLength'], avg_results[ylabel],
             marker='o', linestyle='-', color='b')
    plt.xlabel('Word Length')
    plt.ylabel(ylabel)
    plt.title(title)
    plt.grid(True)
    plt.tight_layout()

    # Save the plot as a PNG file
    plt.savefig(filename)

    # Show the plot
    plt.show()


# Load data from CSV into DataFrame (Wordle experiment results)
df_wordle = pd.read_csv('wordle_experiment_results.csv')

# Plot and save average number of guesses vs word length
plot_and_save_avg_results(
    df_wordle, 'AvgRounds', 'Average Number of Guesses to Find the Secret Word in Wordle', 'avg_guesses_vs_wordle.png')

# Plot and save average time vs word length
plot_and_save_avg_results(
    df_wordle, 'AvgTime', 'Average Time to Find the Secret Word in Wordle', 'avg_time_vs_wordle.png')

# Load data from CSV into DataFrame (Word Challenge experiment results)
df_word_challenge = pd.read_csv('word_challenge_experiment_results.csv')

# Plot and save average number of words found vs word length
plot_and_save_avg_results(df_word_challenge, 'avgWordsFound',
                          'Average Number of Words Found in Word Challenge', 'avg_words_found_vs_word_challenge.png')

# Plot and save average time vs word length
plot_and_save_avg_results(df_word_challenge, 'AvgTime',
                          'Average Time to Find Words in Word Challenge', 'avg_time_vs_word_challenge.png')
