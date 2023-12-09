#ifndef GAMEMODES_H
#define GAMEMODES_H

#include "Game.h"

void PlayerVsComputer(Game& player, Game& computer, bool& playerPlacedShips);
void PlayerVsComputerRandom(Game& player, Game& computer, bool& playerPlacedShips);

void ComputerVsComputer(Game& computer1, Game& computer2);

int EnemyStrike(Game& targetGame);

#endif
