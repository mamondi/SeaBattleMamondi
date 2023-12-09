#include "Gamemodes.h"
#include "Game.h"
#include <iostream>

void PlayerVsComputer(Game& player, Game& computer, bool& playerPlacedShips) {
    while (player.ShipsAmount() > 0 && computer.ShipsAmount() > 0) {
        system("cls");
        cout << "Your field:" << endl;
        player.Show(true);
        cout << "Computer's field:" << endl;
        computer.Show();

        cout << "Your ships left: " << player.ShipsAmount() << endl;

        int pos1, pos2;
        cout << "Input location to attack (row and column): ";
        cin >> pos1 >> pos2;

        if (pos1 < 0 || pos1 >= rows || pos2 < 0 || pos2 >= el) {
            cout << "Invalid input. Try again with valid coordinates." << endl;
            continue;
        }

        if (!player.Strike(pos1, pos2, computer)) {
            cout << "You missed at (" << pos1 << ", " << pos2 << ")!" << endl;
        }
        else {
            cout << "You hit at (" << pos1 << ", " << pos2 << ")!" << endl;
        }

        if (computer.ShipsAmount() == 0) {
            cout << "Congratulations! You won!" << endl;
            break;
        }

        int enemyTurn = EnemyStrike(player);
        int enemyX = enemyTurn / 10;
        int enemyY = enemyTurn % 10;

        if (!computer.Strike(enemyX, enemyY, player)) {
            cout << "Computer missed at (" << enemyX << ", " << enemyY << ")!" << endl;
        }
        else {
            cout << "Computer hit at (" << enemyX << ", " << enemyY << ")!" << endl;
        }

        if (player.ShipsAmount() == 0) {
            cout << "You lost! Better luck next time." << endl;
            break;
        }

        cout << "Press Enter to continue...";
        cin.ignore();
        cin.get();
    }

    cout << "Press Enter to return to the main menu...";
    cin.ignore();
    cin.get();
}




void PlayerVsComputerRandom(Game& player, Game& computer, bool& playerPlacedShips) {
    computer.ComputerPlayerShipsPosition();

    player.ComputerPlayerShipsPosition();
    playerPlacedShips = true;

    while (player.ShipsAmount() > 0) {
        system("cls");
        player.Show(true);
        computer.Show();

        cout << "Your ships left: " << player.ShipsAmount() << endl;

        int pos1, pos2;
        cout << "Input location to attack (row and column): ";
        cin >> pos1 >> pos2;

        if (pos1 < 0 || pos1 >= rows || pos2 < 0 || pos2 >= el) {
            cout << "Invalid input. Try again with valid coordinates." << endl;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            continue;
        }

        if (computer.Strike(pos1, pos2, computer)) {
            cout << "You hit at (" << pos1 << ", " << pos2 << ")!" << endl;
        }
        else {
            cout << "You missed at (" << pos1 << ", " << pos2 << ")!" << endl;
        }

        cout << "Press Enter to continue...";
        cin.ignore();
        cin.get();
        system("cls");

        cout << "Your field:" << endl;
        player.Show(true);
        cout << "Computer's field:" << endl;
        computer.Show();

        cout << "Computer's turn..." << endl;
        int enemyTurn = EnemyStrike(player);
        int enemyX = enemyTurn / 10;
        int enemyY = enemyTurn % 10;

        if (player.Strike(enemyX, enemyY, player)) {
            cout << "Computer hit at (" << enemyX << ", " << enemyY << ")!" << endl;
        }
        else {
            cout << "Computer missed at (" << enemyX << ", " << enemyY << ")!" << endl;
        }

        cout << "Your ships left: " << player.ShipsAmount() << endl;
        cout << "Press Enter to continue...";
        cin.ignore();
        cin.get();
        system("cls");
    }

    system("cls");
    cout << "Your field:" << endl;
    player.Show(true);
    cout << "Computer's field:" << endl;
    computer.Show();

    if (player.ShipsAmount() == 0) {
        cout << "You lost! Better luck next time." << endl;
    }
    else {
        cout << "Congratulations! You won!" << endl;
    }
}

void ComputerVsComputer(Game& computer1, Game& computer2) {
    while (computer1.ShipsAmount() > 0 && computer2.ShipsAmount() > 0) {
        system("cls");
        std::cout << "Computer 1's field:" << std::endl;
        computer1.Show();

        int enemyTurn = EnemyStrike(computer1);
        int enemyX = enemyTurn / 10;
        int enemyY = enemyTurn % 10;

        if (computer1.Strike(enemyX, enemyY, computer1)) {
            std::cout << "Computer 1 hit at (" << enemyX << ", " << enemyY << ")!" << std::endl;
        }
        else {
            std::cout << "Computer 1 missed at (" << enemyX << ", " << enemyY << ")!" << std::endl;
        }

        std::cout << "Computer 1's ships left: " << computer1.ShipsAmount() << std::endl;
        std::cout << "Press Enter to continue...";
        std::cin.ignore();
        std::cin.get();
        system("cls");

        std::cout << "Computer 2's field:" << std::endl;
        computer2.Show();

        enemyTurn = EnemyStrike(computer2);
        enemyX = enemyTurn / 10;
        enemyY = enemyTurn % 10;

        if (computer2.Strike(enemyX, enemyY, computer2)) {
            std::cout << "Computer 2 hit at (" << enemyX << ", " << enemyY << ")!" << std::endl;
        }
        else {
            std::cout << "Computer 2 missed at (" << enemyX << ", " << enemyY << ")!" << std::endl;
        }

        std::cout << "Computer 2's ships left: " << computer2.ShipsAmount() << std::endl;
        std::cout << "Press Enter to continue...";
        std::cin.ignore();
        std::cin.get();
        system("cls");
    }

    system("cls");
    std::cout << "Computer 1's field:" << std::endl;
    computer1.Show();
    std::cout << "Computer 2's field:" << std::endl;
    computer2.Show();

    if (computer1.ShipsAmount() == 0) {
        std::cout << "Computer 1 lost! Computer 2 won!" << std::endl;
    }
    else {
        std::cout << "Computer 2 lost! Computer 1 won!" << std::endl;
    }
}
