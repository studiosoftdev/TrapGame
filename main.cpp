#include <iostream>
#include <windows.h> //needed for Sleep();
#include <cstdlib> //for random stuff
#include <ctime> //needed for time to generate random seed
#include "player.h"

using namespace std;

void initiateGame(int gridSize, int trapCount, int HP);
void menu();
void drawHP(int HP);
void gameLoop(int gridSize, int trapCount, int goalPos[], int playerPos[], int trapPositions[][2], int HP);
void displayGrid(int gridSize, int trapCount, int goalPos[], int playerPos[], int trapPositions[][2]);
int playerMove(char moveKey, int playerPos[]);

int HP = 5;

int main()
{
    Player player;
    menu();
}


void menu(){
    char menuDecision;
    cout << "Welcome to TrapGame. Press P to play, X to exit." << endl;
    cin >> menuDecision;

    if(menuDecision == 80 || menuDecision == 112){
        cout << "game initiated\n";
        cout << "OPTIONS:\n1. Grid size (6-10)";
        int gridSize;
        cin >> gridSize; //length and width of grid. e.g. grid size 6 gives grid of 6x6 or 36 total squares

        if(gridSize > 10){
            cout << "Too big, setting to 10." << endl;
            gridSize = 10;
        }
        if(gridSize < 6){
            cout << "Too small, setting to 6" << endl;
            gridSize = 6;
        }
        cout << "\n2. Number of traps (4-8)";
        int trapCount;
        cin >> trapCount;

        if(trapCount > 8){
            cout << "Too big, setting to 8." << endl;
            trapCount = 8;
        }
        if(trapCount < 4){
            cout << "Too small, setting to 4." << endl;
            trapCount = 4;
        }

        int trapPositions[trapCount][2];
        for(int i = 0; i < trapCount; i++){
            trapPositions[i][0] = rand()%gridSize;
            trapPositions[i][1] = rand()%gridSize;
        }

        char grid[gridSize][gridSize]; //setting game grid
        for(int row = 0; row < gridSize; row++){ //for each row
            for(int col = 0; col < gridSize; col++){ //for each column
                grid[row][col] = 46;
            }
        }
        int playerPos[2] = {(rand()%gridSize), (rand()%gridSize)}; //player coordinates, rand()%gridSize gives a number between 0 and gridSize
        grid[playerPos[0]][playerPos[1]] = 80;

        for(int i = 0; i < trapCount; i++){
            if(grid[trapPositions[i][0]][trapPositions[i][1]] != grid[playerPos[0]][playerPos[1]]){
                grid[trapPositions[i][0]][trapPositions[i][1]] = 84;
            }
        }

        int goalPos[2] = {rand()%gridSize,rand()%gridSize};
        do{
            goalPos[0] = rand()%gridSize;
            goalPos[1] = rand()%gridSize;
        }while(grid[goalPos[0]][goalPos[1]] != 46);

        initiateGame(gridSize, trapCount, HP);
        gameLoop(gridSize, trapCount, goalPos, playerPos, trapPositions, HP);
    }
    if(menuDecision == 88 || menuDecision == 120) {
        cout << "Thanks for playing";
        Sleep(4000);
    }
    if(menuDecision != 80 && menuDecision != 112 && menuDecision != 88 && menuDecision != 120){
        cout << "Invalid option." << endl;
        menu();
    }
}


void initiateGame(int gridSize, int trapCount, int HP){
    char grid[gridSize][gridSize]; //setting game grid
    for(int row = 0; row < gridSize; row++){ //for each row
        for(int col = 0; col < gridSize; col++){ //for each column
            grid[row][col] = 46; //change column contents to . (will later be replaced)
        }
    }
    //Sleep(3000); //so I can see, can later be commented out
    srand(time(0)); //randomise seed using current second elapsed with 1970

    int trapPositions[trapCount][2];
    for(int i = 0; i < trapCount; i++){
        trapPositions[i][0] = rand()%gridSize;
        trapPositions[i][1] = rand()%gridSize;
    }

    int playerPos[2] = {(rand()%gridSize), (rand()%gridSize)}; //player coordinates, rand()%gridSize gives a number between 0 and gridSize
    grid[playerPos[0]][playerPos[1]] = 80;
    for(int i = 0; i < trapCount; i++){
        if(grid[trapPositions[i][0]][trapPositions[i][1]] != grid[playerPos[0]][playerPos[1]]){
            grid[trapPositions[i][0]][trapPositions[i][1]] = 84;
        }
    }
    int goalPos[2] = {rand()%gridSize,rand()%gridSize};
    do{
        goalPos[0] = rand()%gridSize;
        goalPos[1] = rand()%gridSize;
    }while(grid[goalPos[0]][goalPos[1]] != 46);

    displayGrid(gridSize, trapCount, goalPos, playerPos, trapPositions);
    drawHP(HP);
    gameLoop(gridSize, trapCount, goalPos, playerPos, trapPositions, HP);
}



void displayGrid(int gridSize, int trapCount, int goalPos[], int playerPos[], int trapPositions[][2]){
    system("CLS");
    int level = getLevel();
    char grid2[gridSize][gridSize]; //couldn't get grid in here exactly so were just going to make a new one and populate it according to coords of stuff thats on it
    cout << "Level " << level << endl;
    for(int row = 0; row < gridSize; row++){
        for(int col = 0; col < gridSize; col++){
            grid2[row][col] = 46; //creating the bare grid first
        }
    }
    grid2[playerPos[0]][playerPos[1]] = 80; //placing the player according to playerPos on to the grid
    grid2[goalPos[0]][goalPos[1]] = 88;

    for(int i = 0; i < trapCount; i++){ //placing trap positions according to trapPositions
        if(grid2[trapPositions[i][0]][trapPositions[i][1]] != grid2[playerPos[0]][playerPos[1]]){
            grid2[trapPositions[i][0]][trapPositions[i][1]] = 84;
        }
    }
    //time to print out the grid finally
    for(int row = 0; row < gridSize; row++){
        for(int col = 0; col < gridSize; col++){
            cout << grid2[row][col];
        }
        cout << endl;
    }
}

//called after displayGrid ideally
void drawHP (int HP){
    cout << "HP [";
    for(int i = 0; i < HP; i++){
        cout << "::";
    }
    for(int i = HP; i < 5; i++){
        cout << "--";
    }
    cout << "] " << HP << "/5" << endl;
    if(HP == 0){
        int level = getLevel();
        cout << "\n---=== GAME OVER ===---" << "\nMade it to level: " << level << endl;
        Sleep(10000);
        std::_Exit(EXIT_SUCCESS);
    }
}
