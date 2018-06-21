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

void generateScenario(int HP);
void initiateGame(int gridSize, int trapCount, int HP);
void gameLoop();
int getLevel();
void drawHP(int HP);
void displayGrid(int gridSize, int trapCount, int goalPos[], int playerPos[], int trapPositions[][2]);

#endif // PLAYER_H

