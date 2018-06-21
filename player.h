#ifndef PLAYER_H
#define PLAYER_H


class Player
{
    public:
        Player();
        healthManager();
        decreaseHP(int HP, int amount);
        getLevel();
        generateScenario(int HP);
};

bool generateScenario(int HP);
void initiateGame(int gridSize, int trapCount, int HP);
void gameLoop();
int combatLoop(int HP, int eHP, char combatGrid[15][36]);
int getLevel();
void drawHP(int HP);
void displayGrid(int gridSize, int trapCount, int goalPos[], int playerPos[], int trapPositions[][2]);
int enemyAttack(int HP);
int playerAttack(int eHP);
int getHP();
int getGold();

#endif // PLAYER_H

