#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <cstdlib>
#include "player.h"
#include <ctime>
//#include <string>

using namespace std;

void generateScenarioFrame(char combatGrid[15][36], int HP, int eHP);
void drawCombatHP(int HP, int eHP);
void displayBattleInfo(int stance);
void enemyBehaviour();
int combatLoop(int HP, int eHP, char combatGrid[15][36]);
int enemyAttack(int HP);
int playerAttack(int eHP);
int getHP();

int playerPos[2] = {8,12};
int enemyPos[2] = {8,24};
int stance = 0;
bool enemySword = false;
bool attack = false;
bool success = false;
int message;
int newHP;

bool generateScenario(int HP){
    system("CLS");
    playerPos[0] = 8;
    playerPos[1] = 12;
    enemyPos[0] = 8;
    enemyPos[1] = 24;
    stance = 0;
    enemySword = false;
    attack = false;
    int eHP = 5;
    char combatGrid[15][36];
    generateScenarioFrame(combatGrid, HP, eHP);
    HP = combatLoop(HP, eHP, combatGrid);
    return success;
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
            if(enemySword){
                combatGrid[enemyPos[0] - 1][enemyPos[1] - 2] = 88;
                combatGrid[enemyPos[0] - 1][enemyPos[1] - 3] = 88;
            }
            combatGrid[playerPos[0]][playerPos[1]] = 80;
            combatGrid[playerPos[0] - 1][playerPos[1]] = 80;
            combatGrid[playerPos[0]][playerPos[1] - 1] = 80;
            combatGrid[playerPos[0] - 1][playerPos[1] - 1] = 80;
            combatGrid[playerPos[0] - 2][playerPos[1]] = 80;
            combatGrid[playerPos[0] - 2][playerPos[1] - 1] = 80;
            if(attack){
                combatGrid[playerPos[0] - 1][playerPos[1] + 1] = 88;
                combatGrid[playerPos[0] - 1][playerPos[1] + 2] = 88;
            }
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
    for(int i = 0; i < eHP; i++){
        cout << "::";
    }
    cout << "] HP" << endl;
    if(HP == 0){
        cout << "dead";
    }
}


int combatLoop(int HP, int eHP, char combatGrid[15][36]){
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
        if(moveKey == 120){
            stance = 0;
        }
        if(moveKey == 102){
            stance = 1;
        }
        if(moveKey == 101){
            attack = !attack;
        }
        enemyBehaviour();
        if(attack){
            if(combatGrid[playerPos[0] - 1][playerPos[1] + 2] == 84){
                eHP = playerAttack(eHP);
            }
        }
        if(enemySword){
            if(combatGrid[enemyPos[0] - 1][enemyPos[1] - 3] == 80){
                HP = enemyAttack(HP);
            }
        }
        generateScenarioFrame(combatGrid, HP, eHP);
        displayBattleInfo(stance);
        message = 6;
        newHP = HP;
    }while(eHP > 0 && HP > 0);
    if(eHP == 0){
        success = true;
    }
    if(HP == 0){
        success = false;
    }
    return HP;
}


void displayBattleInfo(int stance){
    if(stance == 0){
        cout << "[ATK]" << endl;
    }
    if(stance == 1){
        cout << "[DEF]" << endl;
    }
    if(stance == 2){
        cout << "[PARRY]" << endl;
    }
    switch(message){
        case 0:
            cout << "Attack blocked!";
            break;
        case 1:
            cout << "Enemy hit you!";
            break;
        case 2:
            cout << "Enemy missed you!";
            break;
        case 3:
            cout << "Hit enemy!";
            break;
        case 4:
            cout << "Missed!";
            break;
        case 5:
            cout << "Defence stance. Can't attack.";
            break;
        default:
            cout << " ";
            break;
    }
}


void enemyBehaviour(){
    srand(time(0));
    if(rand()%2 == 0){
        if(enemyPos[1] > 2 && enemyPos[1] < 35){
            enemyPos[1] += rand()%3 - 1;
        }
    }
    if(rand()%2 == 0){
        enemySword = true;
    } else {enemySword = false;}
}


int enemyAttack(int HP){
    if(stance == 1){
        message = 0;
    }
    if(stance == 2){
        if(rand()%10 > 5){
            message = 1;
            HP --;
        }else{
            message = 2;
        }
    }
    if(stance == 0){
        if(rand()%10 < 8){
            message = 1;
            HP--;
        } else {
            message = 2;
        }
    }
    return HP;
}


int playerAttack(int eHP){
    if(stance == 0){
        if(rand()%10 < 8){
            message = 3;
            eHP--;
        } else {
            message = 4;
        }
    }
    if(stance == 1){
        message = 5;
    }
    if(stance == 2){
        if(rand()%10 < 5){
            message = 3;
            eHP--;
        } else {
            message = 4;
        }
    }
    return eHP;
}


int getHP(){
    return newHP;
}
