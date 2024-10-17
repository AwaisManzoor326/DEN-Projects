#include <iostream>
#include <string>

using namespace std;

class Player {
public:
    int health;
    bool hasSword;

    Player() : health(100), hasSword(false) {}

    void displayStats() {
        cout << "Health: " << health << "\n";
        cout << "Sword: " << (hasSword ? "Yes" : "No") << "\n\n";
    }
};

void intro() {
    cout << "\nWelcome to the Adventure Game!\n";
    cout << "You are a brave adventurer, seeking fortune and glory.\n\n";
}

void forestScenario(Player &player) {
    string choice;
    cout << "You are standing in a dark forest. There is a path to the left and one to the right.\n";
    cout << "Where would you like to go? (left/right)\n";
    cin >> choice;

    if (choice == "left") {
        cout << "You encounter a wild beast!\n";
        if (player.hasSword) {
            cout << "You fight it off with your sword and survive.\n";
        } else {
            cout << "You have no weapon and the beast attacks you. You lose 20 health points.\n";
            player.health -= 20;
        }
    } else if (choice == "right") {
        cout << "You find a mysterious chest containing a sword.\n";
        player.hasSword = true;
        cout << "You take the sword.\n";
    } else {
        cout << "Invalid choice! You remain where you are.\n";
    }
}

void caveScenario(Player &player) {
    string choice;
    cout << "You enter a dark cave. There is a treasure chest in the corner.\n";
    cout << "Do you want to open it? (yes/no)\n";
    cin >> choice;

    if (choice == "yes") {
        cout << "You find gold inside the chest, but a trap is triggered! You lose 10 health points.\n";
        player.health -= 10;
    } else {
        cout << "You leave the chest alone and safely exit the cave.\n";
    }
}

int main() {
    Player player;
    string choice;
    intro();

    while (player.health > 0) {
        cout << "Where do you want to go next? (forest/cave/quit)\n";
        cin >> choice;

        if (choice == "forest") {
            forestScenario(player);
        } else if (choice == "cave") {
            caveScenario(player);
        } else if (choice == "quit") {
            cout << "Thanks for playing!\n";
            break;
        } else {
            cout << "Invalid choice. Try again.\n";
        }

        // Show player stats after each scenario
        player.displayStats();

        if (player.health <= 0) {
            cout << "You have died. Game over!\n";
            break;
        }
    }

    return 0;
}