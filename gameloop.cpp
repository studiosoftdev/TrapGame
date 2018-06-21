#include <iostream>
#include <windows.h>
#include "player.h"

using namespace std;

int level = 1;
int newGold = 0;
bool atksuccess = false;
int excludeTraps[10] = {0,0,0,0,0,0,0,0,0};

void endLevel(int gridSize, int trapCount, int HP);
int getLevel();
int getGold();

void gameLoop(int gridSize, int trapCount, int goalPos[], int playerPos[], int trapPositions[][2], int HP){
    Player player;
    do{
        char moveKey;
        cin >> moveKey;

        switch(moveKey){
            case 119:
                if(playerPos[0] > 0){
                    playerPos[0] -= 1;
                }
                break;
            case 115:
                if(playerPos[0] < (gridSize - 1)){
                    playerPos[0] += 1;
                }
                break;
            case 97:
                if(playerPos[1] > 0){
                    playerPos[1] -= 1;
                }
                break;
            case 100:
                if(playerPos[1] < (gridSize - 1)){
                    playerPos[1] += 1;
                }
                break;
            default:
                cout << "\nInvalid movement. Use WASD." << endl;
                break;
        }

        for(int i = 0; i < trapCount; i++){ //check to see if player is on any trap position
            //cout << trapPositions[i][0] << " - " << trapPositions[i][1] << " -- " << playerPos[0] << " - " << playerPos[1] << endl;
            if(playerPos[0] == trapPositions[i][0] && playerPos[1] == trapPositions[i][1]){
                atksuccess = generateScenario(HP);
                HP = getHP();
                if(atksuccess){
                    newGold += (rand()%14) + 7;
                    trapPositions[i][1] = gridSize + 5;
                    excludeTraps[i] = 1;
                }
            }
        }

        //randomise trap positions for random movement of traps
        for (int i = 0; i < trapCount; i++){
            int randMove = rand()%2;
            if(excludeTraps[i] != 1){
                if(randMove == 0){ //if randMove is even, move N/S
                    if(trapPositions[i][0] < (gridSize - 1) && trapPositions[i][0] > 0){ //if not at N/S edge, move +- 1 or not at all
                        trapPositions[i][0] += (rand()%3) - 1;
                    }
                    if(trapPositions[i][0] >= (gridSize - 1)){ //if at south edge
                        trapPositions[i][0] += (rand()%2) - 1; //move not at all or up
                    }
                    if(trapPositions[i][0] <= 0){ //if at north edge
                        trapPositions[i][0] += (rand()%2) + 1; //move not at all or down
                    }
                }
                if(randMove == 1){ //if randMove is odd, move E/W
                    if(trapPositions[i][1] < (gridSize - 1) && trapPositions[i][1] > 0){ //if not at E/W edge, move normally
                        trapPositions[i][1] += (rand()%3) - 1;
                    }
                    if(trapPositions[i][1] >= (gridSize - 1)){ //if at east edge
                        trapPositions[i][1] += (rand()%2) - 1; //move not at all or left
                    }
                    if(trapPositions[i][1] <= 0){ //if at west edge
                        trapPositions[i][1] += (rand()%2) + 1; //move not at all or right
                    }
                }
            }
        }

        displayGrid(gridSize, trapCount, goalPos, playerPos, trapPositions); //draw updated grid
        drawHP(HP); //draw HP added on
        //cout << playerPos[0] << " " << playerPos[1] << " - " << goalPos[0] << " " << goalPos[1];
    }while((playerPos[0] != goalPos[0]) || (playerPos[1] != goalPos[1]));
    endLevel(gridSize, trapCount, HP);
}

//once goal is reached, start new level
void endLevel(int gridSize, int trapCount, int HP){
    level++;
    for(int i = 0;i < 10; i++){
        excludeTraps[i] = 0;
    }
    cout << "\n---=== LEVEL WIN ===---" << endl;
    cout << "Loading level " << level;
    for(int i = 0; i < 3; i++){
        Sleep(1000);
        cout << ".";
    }
    initiateGame(gridSize, trapCount, HP);
}

int getLevel(){
    return level;
}

int getGold(){
    return newGold;
}
