#include <iostream>
#include "player.h"
//I dont know why I even bothered with this but its here anyway
Player::Player()
{
    //constructor
    //eint HP = 10;
}

Player::healthManager(){
    return 0;
}

Player::decreaseHP(int HP, int amount){
    HP -= amount;
    return HP;
}
