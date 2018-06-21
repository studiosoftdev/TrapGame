#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include "player.h"

using namespace std;

void generateScenarioFrame(char combatGrid[15][36], int HP, int eHP);
void drawCombatHP(int HP, int eHP);
void displayBattleInfo(int stance);
void combatLoop(int HP, int eHP, char combatGrid[15][36]);

int playerPos[2] = {8,12};
int enemyPos[2] = {8,24};
int stance = 0;

void generateScenario(int HP){
    system("CLS");
    int eHP = 5;
    char combatGrid[15][36];
    generateScenarioFrame(combatGrid, HP, eHP);
    combatLoop(HP, eHP, combatGrid);
    Sleep(10000);
}


void generateScenarioFrame(char combatGrid[15][36], int HP, int eHP){
    system("CLS");
    for(int row = 0; row < 15; row++){
        for(int col = 0; col < 36; col++){
            combatGrid[row][col] = 46;
            if(combatGrid[0][col] == 46 || combatGrid[14][col] == 46 || combatGrid[row][0] == 46 || combatGrid[row][35] == 46){
                combatGrid[row][col] = 35;
            }
            if(combatGrid[row][col] == 46 && row > 8){
                combatGrid[row][col] = 61;
            }
            combatGrid[playerPos[0]][playerPos[1]] = 80;
            combatGrid[playerPos[0] - 1][playerPos[1]] = 80;
            combatGrid[playerPos[0]][playerPos[1] - 1] = 80;
            combatGrid[playerPos[0] - 1][playerPos[1] - 1] = 80;
            combatGrid[playerPos[0] - 2][playerPos[1]] = 80;
            combatGrid[playerPos[0] - 2][playerPos[1] - 1] = 80;

            combatGrid[enemyPos[0]][enemyPos[1]] = 84;
            combatGrid[enemyPos[0] - 1][enemyPos[1]] = 84;
            combatGrid[enemyPos[0]][enemyPos[1] - 1] = 84;
            combatGrid[enemyPos[0] - 1][enemyPos[1] - 1] = 84;
            combatGrid[enemyPos[0] - 2][enemyPos[1]] = 84;
            combatGrid[enemyPos[0] - 2][enemyPos[1] - 1] = 84;
            cout << combatGrid[row][col];
        }
        cout << endl;
    }
    drawCombatHP(HP, eHP);
}


void drawCombatHP(int HP, int eHP){
    cout << "HP [";
    for(int i = 0; i < HP; i++){
        cout << "::";
    }
    for(int i = HP; i < 5; i++){
        cout << "--";
    }
    cout << "] " << HP << "/5" << " | " << " "<< eHP << "/5" << " [";
    for(int i = eHP; i < 5; i++){
        cout << "--";
    }
    for(int i = 0; i < 5; i++){
        cout << "::";
    }
    cout << "] HP" << endl;
    if(HP == 0){
        cout << "dead";
    }
}


void combatLoop(int HP, int eHP, char combatGrid[15][36]){
    do{
        char moveKey;
        cin >> moveKey;
        if(moveKey == 97){
            if(playerPos[1] > 2){
                    playerPos[1]--;
                }
        }
        if(moveKey == 100){
            if(playerPos[1] < 34){
                    playerPos[1]++;
                }
        }
        if(moveKey == 112){
            stance = 2;
        }
        if(moveKey == 102){
            stance = 0;
        }
        if(moveKey == 120){
            stance = 1;
        }
        if(moveKey == 101){

        }
        generateScenarioFrame(combatGrid, HP, eHP);
        displayBattleInfo(stance);
    }while(HP > 0 || eHP > 0);
}


void displayBattleInfo(int stance){
    if(stance == 0){
        cout << "[DEF]" << endl;
    }
    if(stance == 1){
        cout << "[ATK]" << endl;
    }
    if(stance == 2){
        cout << "[PARRY]" << endl;
    }
}
