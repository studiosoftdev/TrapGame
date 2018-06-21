#include <iostream>
#include "player.h"

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
