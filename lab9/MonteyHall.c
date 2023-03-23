#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    // Seed the random number generator
    srand(time(NULL));
    int doors[3] = {0, 0, 0}; // 0 = null, 1 = prize
    // Place the prize behind one of the doors
    int prize = rand() % 3;
    doors[prize] = 1;


    // Get the player's initial selection
    int selection;
    printf("Choose a door (0, 1, or 2): ");
    scanf("%d", &selection);

    // Check if the selection is valid or try again
    while (selection != 0 && selection != 1 && selection != 2)
    {
        printf("Invalid choice. \n");
        printf("Choose a door (0, 1, or 2): \n");
        scanf("%d", &selection);
    }

    printf("You chose door %d. \n", selection);

    // Choose a door to reveal that is not the prize or the player's initial selection
    int reveal;
    reveal = rand() % 3;
    while (reveal == selection || reveal == prize)
    {
        reveal = rand() % 3;
    }

    // printf("reveal: %d", reveal);

    printf("I'll tell you that the prize is not behind door %d\n", reveal);

    // Ask the player if they want to switch doors
    int choice;
    printf("Do you want to switch doors? (1 for yes, 0 for no): ");
    scanf("%d", &choice);

    if (choice == 1) {
        int new_selection;
        do {
            printf("Choose a different door (0, 1, or 2): ");
            scanf("%d", &new_selection);
        } while (new_selection == selection || new_selection == reveal);
        selection = new_selection;
    }

    // Check if the player wins
    if (doors[selection] == 1) {
        printf("Congratulations! You win!\n");
    } else {
        printf("Sorry, you lose.\n");
    }

    printf ("The prize was behind door %d\n", prize);

    return 0;
}
