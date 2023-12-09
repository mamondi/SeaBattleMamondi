#pragma once
#include "library.h"

struct Game {
private:
    int maxShipLength;
    bool playerPlacedShips = false;
public:
    Game();
    void MainMenu();
    void SetPlayerPlacedShips(bool value) {
        playerPlacedShips = value;
    }
    void Clear();
    void Show(bool showShips = false);
    int ShipsAmount() const;;
    void ComputerVsComputerShipsPosition();
    void PlayerShipsPosition();
    void ComputerPlayerShipsPosition();
    bool Strike(int x, int y, Game& targetGame);
    void RandomlyPlaceEnemyShips();
    int matrix[rows][el];
    int lastStrikeX;
    int lastStrikeY;
    bool lastStrikeSuccessful;
    void SetMaxShipLength(int length) { maxShipLength = length; }
};

int EnemyStrike(Game& targetGame);