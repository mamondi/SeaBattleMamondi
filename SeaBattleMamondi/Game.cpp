#include "Game.h"
#include "library.h"
#include "Gamemodes.h"

Game::Game() {
    maxShipLength = 3;
    Clear();
    lastStrikeX = -1;
    lastStrikeY = -1;
    lastStrikeSuccessful = false;
}

void Game::MainMenu() {
    int choice;
    bool playerPlacedShips = false;
    Game player, computer;

    do {
        system("cls");
        cout << "=== Menu ===" << endl;
        cout << "1. Player vs. Computer" << endl;
        cout << "2. Computer vs. Computer" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            player.SetMaxShipLength(maxship);
            cout << "Choose mode for Player vs. Computer:" << endl;
            cout << "1. Placement of ships on your own" << endl;
            cout << "2. Placement of ships randomly" << endl;
            int playerVsComputerChoice;
            cin >> playerVsComputerChoice;

            if (playerVsComputerChoice == 1) {
                if (!playerPlacedShips) {
                    player.PlayerShipsPosition();
                    computer.RandomlyPlaceEnemyShips();
                    playerPlacedShips = true;
                }
                PlayerVsComputer(player, computer, playerPlacedShips);
            }
            else if (playerVsComputerChoice == 2) {
                PlayerVsComputerRandom(player, computer, playerPlacedShips);
            }
            else {
                cout << "Invalid choice. Please enter 1 or 2." << endl;
            }
            break;
        }
        case 2: {
            Game computer1, computer2;
            computer1.SetMaxShipLength(maxship);
            computer2.SetMaxShipLength(maxship);
            computer1.ComputerPlayerShipsPosition();
            computer2.ComputerPlayerShipsPosition();
            ComputerVsComputer(computer1, computer2);
            break;
        }
        case 3:
            cout << "Exiting the program. Goodbye!" << endl;
            break;
        default:
            cout << "Invalid choice. Please enter a valid option." << endl;
        }

        if (choice != 3) {
            cout << "Press Enter to return to the main menu...";
            cin.ignore();
            cin.get();
        }

    } while (choice != 3);
}


void Game::Clear() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < el; j++) {
            matrix[i][j] = 0;
        }
    }
}


void Game::Show(bool showShips) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    cout << "  ";
    for (int j = 0; j < el; j++) {
        cout << j << " ";
    }
    cout << endl;

    for (int i = 0; i < rows; i++) {
        cout << i << " ";

        for (int j = 0; j < el; j++) {
            if (matrix[i][j] == 0) {
                SetConsoleTextAttribute(hConsole, 9);
                cout << ". ";
            }
            else if (matrix[i][j] == 1 && showShips) {
                SetConsoleTextAttribute(hConsole, 10);
                cout << "O ";
            }
            else if (matrix[i][j] == 2) {
                SetConsoleTextAttribute(hConsole, 12);
                cout << "Х ";
            }
            else if (matrix[i][j] == 3) {
                SetConsoleTextAttribute(hConsole, 11);
                cout << "X ";
            }
            else {
                SetConsoleTextAttribute(hConsole, 9);
                cout << ". ";
            }
        }
        SetConsoleTextAttribute(hConsole, 7);
        cout << endl;
    }
}

int Game::ShipsAmount() const {
    int amount = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < el; j++) {
            if (matrix[i][j] == 1) {
                amount++;
            }
        }
    }
    return amount;
}

void Game::PlayerShipsPosition() {
    int ship = 0;

    while (ship < maxship) {
        system("cls");
        Show(true);

        // Отримання довжини корабля від користувача
        int shipLength;
        cout << "Enter the length of your ship #" << ship + 1 << ": ";
        cin >> shipLength;

        // Перевірка коректності введеного значення
        if (shipLength < 1 || shipLength > maxShipLength) {
            cout << "Invalid ship length. Try again with a valid length." << endl;
            continue;
        }

        cout << "Place your ship #" << ship + 1 << " (length " << shipLength << "):" << endl;

        // Отримання координат початку корабля від користувача
        cout << "Enter the starting position (row and column): ";
        int x, y;
        cin >> x >> y;

        // Перевірка коректності введених координат
        if (x < 0 || x >= rows || y < 0 || y >= el) {
            cout << "Invalid placement. Try again with valid coordinates." << endl;
            continue;
        }

        bool canPlaceShip = true;

        // Перевірка, чи можна розмістити корабель в обраному місці
        for (int i = 0; i < shipLength; i++) {
            if (matrix[x][y + i] == 1 || y + i >= el) {
                canPlaceShip = false;
                break;
            }
        }

        if (canPlaceShip) {
            // Розміщення корабля на полі
            for (int i = 0; i < shipLength; i++) {
                matrix[x][y + i] = 1;
            }
            ship++;

            // Перевірка, чи всі кораблі вже розставлені
            if (ship == maxship) {
                cout << "You have placed all your ships. Press Enter to continue...";
                cin.ignore();
                cin.get();
                playerPlacedShips = true;
                break;
            }
        }
        else {
            cout << "Cannot place ship there. Try again." << endl;
        }
    }
}

void Game::RandomlyPlaceEnemyShips() {
    int ship = 0;

    while (ship < maxship) {
        int shipLength = rand() % 3 + 1;

        int x = rand() % rows;
        int y = rand() % (el - shipLength + 1);

        bool canPlaceShip = true;

        for (int i = 0; i < shipLength; i++) {
            if (matrix[x][y + i] == 1) {
                canPlaceShip = false;
                break;
            }
        }

        if (canPlaceShip) {
            for (int i = 0; i < shipLength; i++) {
                matrix[x][y + i] = 1;
            }
            ship++;
        }
    }
}


// Генерація полів для комп'ютера в режимі гравець проти комп'ютера
void Game::ComputerPlayerShipsPosition() {
    int ship = 0;

    while (ship < maxship) {
        int shipLength = rand() % 3 + 1;

        int x = rand() % rows;
        int y = rand() % (el - shipLength + 1);

        bool canPlaceShip = true;

        for (int i = 0; i < shipLength; i++) {
            if (matrix[x][y + i] == 1) {
                canPlaceShip = false;
                break;
            }
        }

        if (canPlaceShip) {
            for (int i = 0; i < shipLength; i++) {
                matrix[x][y + i] = 1;
            }
            ship++;
        }
    }
}

// Генерація полів для комп'ютера в режимі комп'ютер проти комп'ютера
void Game::ComputerVsComputerShipsPosition() {
    int ship = 0;

    while (ship < maxship) {
        int shipLength = rand() % 3 + 1;

        int x = rand() % rows;
        int y = rand() % (el - shipLength + 1);

        bool canPlaceShip = true;

        for (int i = 0; i < shipLength; i++) {
            if (matrix[x][y + i] == 1) {
                canPlaceShip = false;
                break;
            }
        }

        if (canPlaceShip) {
            for (int i = 0; i < shipLength; i++) {
                matrix[x][y + i] = 1;
            }
            ship++;
        }
    }
}


bool Game::Strike(int x, int y, Game& targetGame) {
    if (targetGame.matrix[x][y] == 1) {
        targetGame.matrix[x][y] = 2;
        return true;
    }
    else {
        targetGame.matrix[x][y] = 3;
        return false;
    }
}

int EnemyStrike(Game& targetGame) {
    int x = rand() % rows;
    int y = rand() % el;

    targetGame.lastStrikeX = x;
    targetGame.lastStrikeY = y;

    targetGame.Strike(x, y, targetGame);

    if (targetGame.lastStrikeSuccessful) {
        targetGame.matrix[x][y] = 2;
    }

    return x * 10 + y;
}
