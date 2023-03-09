#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_ATTEMPTS 6
#define WORD_LENGTH 4

int main() {
    char word[WORD_LENGTH + 1];
    char guess[WORD_LENGTH + 1];
    char correct_letters[WORD_LENGTH + 1];
    char incorrect_positions[WORD_LENGTH + 1];
    int i, j;
    int num_attempts = 0;
    int num_correct = 0;
    int correct_positions[WORD_LENGTH];
    int invalid_guess = 0;

    srand(time(NULL));

    // Choose a random 4-letter word
    const char* word_list[] = {"atom", "bath", "chef", "dice", "evil", "fate", "gold", "hawk", "inch", "java", "kite", "lake", "mate", "nerd"};
    int num_words = sizeof(word_list) / sizeof(word_list[0]);
    int word_index = rand() % num_words;
    strcpy(word, word_list[word_index]);

    // Main game loop
    while (num_attempts < MAX_ATTEMPTS && num_correct < WORD_LENGTH) {
        invalid_guess = 0;
        // Get user input
        do {
            printf("Enter a 4-letter word: ");
            scanf("%s", guess);
            if(strlen(guess) != WORD_LENGTH){
                printf("Please enter a 4-letter word.\n");
                invalid_guess = 1;
            }else{
                invalid_guess = 0;
            }
        } while (invalid_guess);

        // Check for correct letters and positions
        num_correct = 0;
        for (i = 0; i < WORD_LENGTH; i++) {
            if (guess[i] == word[i]) {
                num_correct++;
                correct_positions[i] = 1;
                correct_letters[i] = guess[i];
            } else {
                correct_positions[i] = 0;
                correct_letters[i] = '-';
            }
        }
        correct_letters[WORD_LENGTH] = '\0';

        // Check for correct letters in incorrect positions
        int num_incorrect = 0;
        for (i = 0; i < WORD_LENGTH; i++) {
            if (!correct_positions[i]) {
                for (j = 0; j < WORD_LENGTH; j++) {
                    if (i != j && guess[i] == word[j]) {
                        // Check if the letter is already in the incorrect positions array
                        int already_found = 0;
                        for (int k = 0; k < num_incorrect; k++) {
                            if (guess[i] == incorrect_positions[k]) {
                                already_found = 1;
                                break;
                            }
                        }
                        if (!already_found) {
                            incorrect_positions[num_incorrect] = guess[i];
                            num_incorrect++;
                        }
                        break;
                    }
                }
            }
        }
        incorrect_positions[num_incorrect] = '\0';

        // Print feedback
        printf("%s %d correct letter(s), %d letter(s) in the wrong position: %s\n", correct_letters, num_correct, num_incorrect, incorrect_positions);
        num_attempts++;
        printf("You have %d attempt(s) left.\n", MAX_ATTEMPTS - num_attempts);
        printf("------------------------------------------------\n");
    }

    // Print result
    if (num_correct == WORD_LENGTH) {
        printf("Congratulations! You guessed the word in %d attempt(s).\n", num_attempts);
    } else {
        printf("Sorry, you failed to guess the word in %d attempt(s). The word was %s.\n", MAX_ATTEMPTS, word);
    }

    return 0;
}
