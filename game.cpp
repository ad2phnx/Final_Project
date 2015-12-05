
// File: game.cpp
// Game class implementation

#include "game.h"

// Member functions
// Constructors
game::game()
{

}

void game::set_player_turn(int Player_Turn)
{
    this->Player_Turn = Player_Turn;
}

int game::get_player_turn()
{
    return this->Player_Turn;
}
