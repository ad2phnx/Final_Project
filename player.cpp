
// File: player.cpp
// Player class implementation

#include "player.h"
#include <iostream>
using namespace std;

// Member functions
// Constructors
player::player()
{
    this->Score = 0;
    this->Miss_Turn = false;
}

void player::set_name(string Name)
{
    this->Name = Name;
}

string player::get_name()
{
    return this->Name;
}

void player::set_pos(int Pos)
{
    this->Pos = Pos;
}

int player::get_pos()
{
    return this->Pos;
}

void player::set_score(int Score)
{
    this->Score = Score;
}

int player::get_score()
{
    return this->Score;
}

void player::set_turn(bool Miss_Turn)
{
    this->Miss_Turn = Miss_Turn;
}

bool player::get_turn()
{
    return this->Miss_Turn;
}
