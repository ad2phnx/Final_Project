// File: player.cpp
// Player class implementation

#include "player.h"
#include <iostream>
using namespace std;

// Member functions
// Constructors
player::player()
{
    // set initial player info
    this->Score = 0;
    this->Tot_Score = 0;
    this->Miss_Turn = false;
}

// set name of player
void player::set_name(string Name)
{
    this->Name = Name;
}

// get player name (short or long)
string player::get_name(bool Short)
{
    string Name;

    if (Short)
        Name = this->Name.substr(0,10);
    else
        Name = this->Name;

    return Name;
}

// set position of player
void player::set_pos(int Pos)
{
    this->Pos = Pos;
}

// get players position
int player::get_pos()
{
    return this->Pos;
}

// set score of player
void player::set_score(int Score)
{
    this->Score = Score;
}

// get score of player
int player::get_score()
{
    return this->Score;
}

// set total score of player
void player::set_tot_score(int Tot_Score)
{
    this->Tot_Score = Tot_Score;
}

// get players total score
int player::get_tot_score()
{
    return Tot_Score;
}

// set if player misses next turn
void player::set_turn_miss(bool Miss_Turn)
{
    this->Miss_Turn = Miss_Turn;
}

// get if player misses next turn
bool player::get_turn_miss()
{
    return this->Miss_Turn;
}
